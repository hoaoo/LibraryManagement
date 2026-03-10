#include "BorrowTab.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QDateEdit>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDate>
#include <QAbstractItemView>
#include <QLabel>

BorrowTab::BorrowTab(LibraryManager& manager, QWidget *parent)
    : QWidget(parent), manager(manager) {
    setupUi();
    loadHistory();
}

void BorrowTab::setupUi() {
    auto *mainLayout = new QVBoxLayout(this);

    // Tiêu đề chính của tab
    auto *titleLabel = new QLabel("Borrow / Return", this);
    titleLabel->setStyleSheet(
        "QLabel { font-size: 22px; font-weight: 700; color: #0f172a; padding: 4px 0 10px 0; }"
    );

    // Chia giao diện thành 2 cột:
    // - Bên trái: form mượn và trả
    // - Bên phải: bảng lịch sử
    auto *contentLayout = new QHBoxLayout();
    auto *leftLayout = new QVBoxLayout();
    auto *rightLayout = new QVBoxLayout();

    // =========================
    // KHU VỰC MƯỢN SÁCH
    // =========================
    auto *borrowGroup = new QGroupBox("Borrow Book", this);
    auto *borrowForm = new QFormLayout();

    readerIdEdit = new QLineEdit(this);
    bookIdEdit = new QLineEdit(this);

    // Dùng QDateEdit và ép format hiển thị theo đúng dữ liệu file: yyyy-MM-dd
    borrowDateEdit = new QDateEdit(QDate::currentDate(), this);
    borrowDateEdit->setCalendarPopup(true);
    borrowDateEdit->setDisplayFormat("yyyy-MM-dd");

    borrowButton = new QPushButton("Borrow", this);
    borrowButton->setStyleSheet(
        "QPushButton { background:#2563eb; color:white; border:none; border-radius:10px; padding:8px 14px; font-weight:600; }"
        "QPushButton:hover { background:#1d4ed8; }"
    );

    borrowForm->addRow("Reader ID:", readerIdEdit);
    borrowForm->addRow("Book ID:", bookIdEdit);
    borrowForm->addRow("Borrow Date:", borrowDateEdit);
    borrowForm->addRow(borrowButton);
    borrowGroup->setLayout(borrowForm);

    // =========================
    // KHU VỰC TRẢ SÁCH
    // =========================
    auto *returnGroup = new QGroupBox("Return Book", this);
    auto *returnForm = new QFormLayout();

    returnReaderIdEdit = new QLineEdit(this);
    returnBookIdEdit = new QLineEdit(this);

    // Giữ cùng format yyyy-MM-dd để đồng bộ với file data
    returnDateEdit = new QDateEdit(QDate::currentDate(), this);
    returnDateEdit->setCalendarPopup(true);
    returnDateEdit->setDisplayFormat("yyyy-MM-dd");

    returnButton = new QPushButton("Return", this);
    returnButton->setStyleSheet(
        "QPushButton { background:#f59e0b; color:white; border:none; border-radius:10px; padding:8px 14px; font-weight:600; }"
        "QPushButton:hover { background:#d97706; }"
    );

    returnForm->addRow("Reader ID:", returnReaderIdEdit);
    returnForm->addRow("Book ID:", returnBookIdEdit);
    returnForm->addRow("Return Date:", returnDateEdit);
    returnForm->addRow(returnButton);
    returnGroup->setLayout(returnForm);

    // Nút làm mới lịch sử
    refreshButton = new QPushButton("Refresh History", this);
    refreshButton->setStyleSheet(
        "QPushButton { background:#64748b; color:white; border:none; border-radius:10px; padding:8px 14px; font-weight:600; }"
        "QPushButton:hover { background:#475569; }"
    );

    // =========================
    // BẢNG LỊCH SỬ MƯỢN / TRẢ
    // =========================
    historyTable = new QTableWidget(this);
    historyTable->setColumnCount(6);
    historyTable->setHorizontalHeaderLabels({
        "Record ID", "Reader ID", "Book ID", "Borrow Date", "Return Date", "Status"
    });
    historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    historyTable->setSelectionMode(QAbstractItemView::SingleSelection);
    historyTable->verticalHeader()->setVisible(false);
    historyTable->setAlternatingRowColors(true);
    historyTable->setShowGrid(false);
    historyTable->setStyleSheet("QTableWidget::item { padding: 8px; }");

    // Ghép layout trái
    leftLayout->addWidget(borrowGroup);
    leftLayout->addWidget(returnGroup);
    leftLayout->addStretch();

    // Ghép layout phải
    rightLayout->addWidget(refreshButton);
    rightLayout->addWidget(historyTable);

    // Ghép 2 cột vào layout chính
    contentLayout->addLayout(leftLayout, 1);
    contentLayout->addLayout(rightLayout, 2);

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(contentLayout);

    // Kết nối signal-slot
    connect(borrowButton, &QPushButton::clicked, this, &BorrowTab::onBorrowBook);
    connect(returnButton, &QPushButton::clicked, this, &BorrowTab::onReturnBook);
    connect(refreshButton, &QPushButton::clicked, this, &BorrowTab::onRefreshHistory);
}

void BorrowTab::loadHistory() {
    historyTable->setRowCount(0);

    const auto& records = manager.getBorrowRecords();
    for (int i = 0; i < static_cast<int>(records.size()); ++i) {
        historyTable->insertRow(i);
        historyTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(records[i].getRecordId())));
        historyTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(records[i].getReaderId())));
        historyTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(records[i].getBookId())));
        historyTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(records[i].getBorrowDate())));
        historyTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(records[i].getReturnDate())));
        historyTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(records[i].getStatus())));
    }
}

void BorrowTab::onBorrowBook() {
    QString readerId = readerIdEdit->text().trimmed();
    QString bookId = bookIdEdit->text().trimmed();

    // Chuyển ngày sang đúng format lưu file
    QString borrowDate = borrowDateEdit->date().toString("yyyy-MM-dd");

    if (readerId.isEmpty() || bookId.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Reader ID và Book ID không được để trống.");
        return;
    }

    if (!manager.borrowBookGUI(readerId.toStdString(), bookId.toStdString(), borrowDate.toStdString())) {
        QMessageBox::warning(this, "Borrow Book", "Không thể mượn sách.\nKiểm tra lại Reader ID, Book ID hoặc số lượng sách còn lại.");
        return;
    }

    loadHistory();
    QMessageBox::information(this, "Borrow Book", "Mượn sách thành công.");

    readerIdEdit->clear();
    bookIdEdit->clear();
}

void BorrowTab::onReturnBook() {
    QString readerId = returnReaderIdEdit->text().trimmed();
    QString bookId = returnBookIdEdit->text().trimmed();

    // Chuyển ngày sang đúng format lưu file
    QString returnDate = returnDateEdit->date().toString("yyyy-MM-dd");

    if (readerId.isEmpty() || bookId.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Reader ID và Book ID không được để trống.");
        return;
    }

    if (!manager.returnBookGUI(readerId.toStdString(), bookId.toStdString(), returnDate.toStdString())) {
        QMessageBox::warning(this, "Return Book", "Không tìm thấy bản ghi mượn phù hợp để trả.");
        return;
    }

    loadHistory();
    QMessageBox::information(this, "Return Book", "Trả sách thành công.");

    returnReaderIdEdit->clear();
    returnBookIdEdit->clear();
}

void BorrowTab::onRefreshHistory() {
    manager.loadBorrowRecords();
    manager.loadBooks();
    loadHistory();
}