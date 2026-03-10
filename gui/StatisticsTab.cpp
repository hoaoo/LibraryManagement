#include "StatisticsTab.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QTableWidgetItem>
#include <QAbstractItemView>

StatisticsTab::StatisticsTab(LibraryManager& manager, QWidget *parent)
    : QWidget(parent), manager(manager) {
    setupUi();
    loadStatistics();
}

void StatisticsTab::setupUi() {
    auto *mainLayout = new QVBoxLayout(this);

    auto *titleLabel = new QLabel("Statistics Dashboard", this);
    titleLabel->setStyleSheet(
        "QLabel { font-size: 22px; font-weight: 700; color: #0f172a; padding: 4px 0 10px 0; }"
    );

    auto *statsGroup = new QGroupBox("Overview", this);
    auto *statsLayout = new QGridLayout();

    totalBooksLabel = new QLabel("Total books: 0", this);
    totalReadersLabel = new QLabel("Total readers: 0", this);
    borrowingBooksLabel = new QLabel("Books being borrowed: 0", this);
    outOfStockBooksLabel = new QLabel("Out of stock books: 0", this);

    // Style dạng thẻ dashboard
    QString cardStyle =
        "QLabel {"
        "background:#f8fbff;"
        "border:1px solid #dbeafe;"
        "border-radius:12px;"
        "padding:16px;"
        "font-size:15px;"
        "font-weight:700;"
        "color:#1e3a8a;"
        "}";

    totalBooksLabel->setStyleSheet(cardStyle);
    totalReadersLabel->setStyleSheet(cardStyle);
    borrowingBooksLabel->setStyleSheet(cardStyle);
    outOfStockBooksLabel->setStyleSheet(cardStyle);

    statsLayout->addWidget(totalBooksLabel, 0, 0);
    statsLayout->addWidget(totalReadersLabel, 0, 1);
    statsLayout->addWidget(borrowingBooksLabel, 1, 0);
    statsLayout->addWidget(outOfStockBooksLabel, 1, 1);

    statsGroup->setLayout(statsLayout);

    auto *borrowingGroup = new QGroupBox("Books Currently Borrowed", this);
    auto *borrowingLayout = new QVBoxLayout();
    borrowingTable = new QTableWidget(this);
    borrowingTable->setColumnCount(5);
    borrowingTable->setHorizontalHeaderLabels({
        "Record ID", "Book ID", "Title", "Reader ID", "Borrow Date"
    });
    borrowingTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    borrowingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    borrowingTable->verticalHeader()->setVisible(false);
    borrowingTable->setAlternatingRowColors(true);
    borrowingTable->setShowGrid(false);
    borrowingTable->setStyleSheet("QTableWidget::item { padding: 8px; }");
    borrowingLayout->addWidget(borrowingTable);
    borrowingGroup->setLayout(borrowingLayout);

    auto *outOfStockGroup = new QGroupBox("Out of Stock Books", this);
    auto *outOfStockLayout = new QVBoxLayout();
    outOfStockTable = new QTableWidget(this);
    outOfStockTable->setColumnCount(4);
    outOfStockTable->setHorizontalHeaderLabels({
        "Book ID", "Title", "Author", "Available"
    });
    outOfStockTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    outOfStockTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    outOfStockTable->verticalHeader()->setVisible(false);
    outOfStockTable->setAlternatingRowColors(true);
    outOfStockTable->setShowGrid(false);
    outOfStockTable->setStyleSheet("QTableWidget::item { padding: 8px; }");
    outOfStockLayout->addWidget(outOfStockTable);
    outOfStockGroup->setLayout(outOfStockLayout);

    refreshButton = new QPushButton("Refresh Statistics", this);
    refreshButton->setStyleSheet(
        "QPushButton { background:#0f172a; color:white; border:none; border-radius:10px; padding:8px 14px; font-weight:600; }"
        "QPushButton:hover { background:#1e293b; }"
    );

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(statsGroup);
    mainLayout->addWidget(borrowingGroup);
    mainLayout->addWidget(outOfStockGroup);
    mainLayout->addWidget(refreshButton);

    connect(refreshButton, &QPushButton::clicked, this, &StatisticsTab::onRefreshStatistics);
}

void StatisticsTab::loadStatistics() {
    totalBooksLabel->setText("Total books: " + QString::number(manager.getTotalBooksCountGUI()));
    totalReadersLabel->setText("Total readers: " + QString::number(manager.getTotalReadersCountGUI()));
    borrowingBooksLabel->setText("Books being borrowed: " + QString::number(manager.getBorrowingCountGUI()));
    outOfStockBooksLabel->setText("Out of stock books: " + QString::number(static_cast<int>(manager.getOutOfStockBooksGUI().size())));

    borrowingTable->setRowCount(0);
    auto borrowingRecords = manager.getBorrowingRecordsGUI();
    for (int i = 0; i < static_cast<int>(borrowingRecords.size()); ++i) {
        borrowingTable->insertRow(i);
        borrowingTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(borrowingRecords[i].getRecordId())));
        borrowingTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(borrowingRecords[i].getBookId())));
        borrowingTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(manager.getBookTitleByIdGUI(borrowingRecords[i].getBookId()))));
        borrowingTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(borrowingRecords[i].getReaderId())));
        borrowingTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(borrowingRecords[i].getBorrowDate())));
    }

    outOfStockTable->setRowCount(0);
    auto outOfStockBooks = manager.getOutOfStockBooksGUI();
    for (int i = 0; i < static_cast<int>(outOfStockBooks.size()); ++i) {
        outOfStockTable->insertRow(i);
        outOfStockTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(outOfStockBooks[i].getBookId())));
        outOfStockTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(outOfStockBooks[i].getTitle())));
        outOfStockTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(outOfStockBooks[i].getAuthor())));
        outOfStockTable->setItem(i, 3, new QTableWidgetItem(QString::number(outOfStockBooks[i].getAvailable())));
    }
}

void StatisticsTab::onRefreshStatistics() {
    manager.loadBooks();
    manager.loadReaders();
    manager.loadBorrowRecords();
    loadStatistics();
}