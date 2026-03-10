#include "BorrowTab.h"

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

BorrowTab::BorrowTab(LibraryManager& manager, QWidget *parent)
    : QWidget(parent), manager(manager) {
    setupUi();
    loadHistory();
}

void BorrowTab::setupUi() {
    auto *mainLayout = new QVBoxLayout(this);

    auto *borrowGroup = new QGroupBox("Borrow Book", this);
    auto *borrowForm = new QFormLayout();

    readerIdEdit = new QLineEdit(this);
    bookIdEdit = new QLineEdit(this);
    borrowDateEdit = new QDateEdit(QDate::currentDate(), this);
    borrowDateEdit->setCalendarPopup(true);

    borrowButton = new QPushButton("Borrow", this);

    borrowForm->addRow("Reader ID:", readerIdEdit);
    borrowForm->addRow("Book ID:", bookIdEdit);
    borrowForm->addRow("Borrow Date:", borrowDateEdit);
    borrowForm->addRow(borrowButton);
    borrowGroup->setLayout(borrowForm);

    auto *returnGroup = new QGroupBox("Return Book", this);
    auto *returnForm = new QFormLayout();

    returnReaderIdEdit = new QLineEdit(this);
    returnBookIdEdit = new QLineEdit(this);
    returnDateEdit = new QDateEdit(QDate::currentDate(), this);
    returnDateEdit->setCalendarPopup(true);
    returnButton = new QPushButton("Return", this);

    returnForm->addRow("Reader ID:", returnReaderIdEdit);
    returnForm->addRow("Book ID:", returnBookIdEdit);
    returnForm->addRow("Return Date:", returnDateEdit);
    returnForm->addRow(returnButton);
    returnGroup->setLayout(returnForm);

    refreshButton = new QPushButton("Refresh History", this);

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

    mainLayout->addWidget(borrowGroup);
    mainLayout->addWidget(returnGroup);
    mainLayout->addWidget(refreshButton);
    mainLayout->addWidget(historyTable);

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