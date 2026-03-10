#include "ReaderTab.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QLabel>
#include <QInputDialog>
#include <QAbstractItemView>

ReaderTab::ReaderTab(LibraryManager& manager, QWidget *parent)
    : QWidget(parent), manager(manager) {
    setupUi();
    loadReaders();
}

void ReaderTab::setupUi() {
    auto *mainLayout = new QVBoxLayout(this);

    auto *titleLabel = new QLabel("Reader Management", this);
    titleLabel->setStyleSheet(
        "QLabel { font-size: 22px; font-weight: 700; color: #0f172a; padding: 4px 0 10px 0; }"
    );

    auto *topLayout = new QHBoxLayout();
    auto *buttonLayout = new QHBoxLayout();

    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search readers by ID, name, phone...");

    addButton = new QPushButton("Add", this);
    editButton = new QPushButton("Edit", this);
    deleteButton = new QPushButton("Delete", this);
    refreshButton = new QPushButton("Refresh", this);

    addButton->setStyleSheet(
        "QPushButton { background:#22c55e; color:white; border:none; border-radius:10px; padding:8px 14px; font-weight:600; }"
        "QPushButton:hover { background:#16a34a; }"
    );
    editButton->setStyleSheet(
        "QPushButton { background:#3b82f6; color:white; border:none; border-radius:10px; padding:8px 14px; font-weight:600; }"
        "QPushButton:hover { background:#2563eb; }"
    );
    deleteButton->setStyleSheet(
        "QPushButton { background:#ef4444; color:white; border:none; border-radius:10px; padding:8px 14px; font-weight:600; }"
        "QPushButton:hover { background:#dc2626; }"
    );
    refreshButton->setStyleSheet(
        "QPushButton { background:#64748b; color:white; border:none; border-radius:10px; padding:8px 14px; font-weight:600; }"
        "QPushButton:hover { background:#475569; }"
    );

    topLayout->addWidget(new QLabel("Search:", this));
    topLayout->addWidget(searchEdit);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addStretch();

    readerTable = new QTableWidget(this);
    readerTable->setColumnCount(4);
    readerTable->setHorizontalHeaderLabels({
        "Reader ID", "Name", "Phone", "Email"
    });
    readerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    readerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    readerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    readerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    readerTable->verticalHeader()->setVisible(false);
    readerTable->setAlternatingRowColors(true);
    readerTable->setShowGrid(false);
    readerTable->setStyleSheet("QTableWidget::item { padding: 8px; }");

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(readerTable);

    connect(addButton, &QPushButton::clicked, this, &ReaderTab::onAddReader);
    connect(editButton, &QPushButton::clicked, this, &ReaderTab::onEditReader);
    connect(deleteButton, &QPushButton::clicked, this, &ReaderTab::onDeleteReader);
    connect(refreshButton, &QPushButton::clicked, this, &ReaderTab::onRefreshReaders);
    connect(searchEdit, &QLineEdit::textChanged, this, &ReaderTab::onSearchTextChanged);
}

void ReaderTab::loadReaders() {
    readerTable->setRowCount(0);

    const auto& readers = manager.getReaders();
    for (int i = 0; i < static_cast<int>(readers.size()); ++i) {
        readerTable->insertRow(i);
        readerTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(readers[i].getReaderId())));
        readerTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(readers[i].getName())));
        readerTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(readers[i].getPhone())));
        readerTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(readers[i].getEmail())));
    }
}

void ReaderTab::filterReaders(const QString &keyword) {
    for (int row = 0; row < readerTable->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < readerTable->columnCount(); ++col) {
            auto *item = readerTable->item(row, col);
            if (item && item->text().contains(keyword, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        readerTable->setRowHidden(row, !match);
    }
}

int ReaderTab::selectedRow() const {
    auto items = readerTable->selectionModel()->selectedRows();
    if (items.isEmpty()) return -1;
    return items.first().row();
}

void ReaderTab::onAddReader() {
    bool ok;

    QString id = QInputDialog::getText(this, "Add Reader", "Reader ID:", QLineEdit::Normal, "", &ok);
    if (!ok || id.trimmed().isEmpty()) return;

    QString name = QInputDialog::getText(this, "Add Reader", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;

    QString phone = QInputDialog::getText(this, "Add Reader", "Phone:", QLineEdit::Normal, "", &ok);
    if (!ok || phone.trimmed().isEmpty()) return;

    QString email = QInputDialog::getText(this, "Add Reader", "Email:", QLineEdit::Normal, "", &ok);
    if (!ok || email.trimmed().isEmpty()) return;

    Reader reader(
        id.trimmed().toStdString(),
        name.trimmed().toStdString(),
        phone.trimmed().toStdString(),
        email.trimmed().toStdString()
    );

    if (!manager.addReaderGUI(reader)) {
        QMessageBox::warning(this, "Add Reader", "Không thể thêm độc giả. Có thể mã độc giả đã tồn tại.");
        return;
    }

    loadReaders();
    QMessageBox::information(this, "Add Reader", "Thêm độc giả thành công.");
}

void ReaderTab::onEditReader() {
    int row = selectedRow();
    if (row < 0) {
        QMessageBox::warning(this, "Edit Reader", "Vui lòng chọn một độc giả để sửa.");
        return;
    }

    QString oldId = readerTable->item(row, 0)->text();
    QString oldName = readerTable->item(row, 1)->text();
    QString oldPhone = readerTable->item(row, 2)->text();
    QString oldEmail = readerTable->item(row, 3)->text();

    bool ok;

    QString newId = QInputDialog::getText(this, "Edit Reader", "Reader ID:", QLineEdit::Normal, oldId, &ok);
    if (!ok || newId.trimmed().isEmpty()) return;

    QString newName = QInputDialog::getText(this, "Edit Reader", "Name:", QLineEdit::Normal, oldName, &ok);
    if (!ok || newName.trimmed().isEmpty()) return;

    QString newPhone = QInputDialog::getText(this, "Edit Reader", "Phone:", QLineEdit::Normal, oldPhone, &ok);
    if (!ok || newPhone.trimmed().isEmpty()) return;

    QString newEmail = QInputDialog::getText(this, "Edit Reader", "Email:", QLineEdit::Normal, oldEmail, &ok);
    if (!ok || newEmail.trimmed().isEmpty()) return;

    Reader updatedReader(
        newId.trimmed().toStdString(),
        newName.trimmed().toStdString(),
        newPhone.trimmed().toStdString(),
        newEmail.trimmed().toStdString()
    );

    if (!manager.updateReaderGUI(oldId.toStdString(), updatedReader)) {
        QMessageBox::warning(this, "Edit Reader", "Không thể cập nhật độc giả.");
        return;
    }

    loadReaders();
    QMessageBox::information(this, "Edit Reader", "Cập nhật độc giả thành công.");
}

void ReaderTab::onDeleteReader() {
    int row = selectedRow();
    if (row < 0) {
        QMessageBox::warning(this, "Delete Reader", "Vui lòng chọn một độc giả để xóa.");
        return;
    }

    QString readerId = readerTable->item(row, 0)->text();

    auto reply = QMessageBox::question(this, "Delete Reader", "Bạn có chắc muốn xóa độc giả đã chọn?");
    if (reply != QMessageBox::Yes) return;

    if (!manager.deleteReaderGUI(readerId.toStdString())) {
        QMessageBox::warning(this, "Delete Reader", "Không thể xóa độc giả. Có thể độc giả đang mượn sách.");
        return;
    }

    loadReaders();
    QMessageBox::information(this, "Delete Reader", "Xóa độc giả thành công.");
}

void ReaderTab::onRefreshReaders() {
    manager.loadReaders();
    loadReaders();
}

void ReaderTab::onSearchTextChanged(const QString &text) {
    filterReaders(text);
}