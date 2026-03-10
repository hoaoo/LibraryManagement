#include "MainWindow.h"
#include "BookTab.h"
#include "ReaderTab.h"
#include "BorrowTab.h"
#include "StatisticsTab.h"

#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      tabWidget(nullptr),
      bookTab(nullptr),
      readerTab(nullptr),
      borrowTab(nullptr),
      statisticsTab(nullptr) {
    manager.loadBooks();
    manager.loadReaders();
    manager.loadBorrowRecords();

    setupUi();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi() {
    setWindowTitle("Library Management System");
    resize(1200, 750);

    tabWidget = new QTabWidget(this);

    bookTab = new BookTab(manager, this);
    readerTab = new ReaderTab(manager, this);
    borrowTab = new BorrowTab(manager, this);
    statisticsTab = new StatisticsTab(manager, this);

    tabWidget->addTab(bookTab, "Book Management");
    tabWidget->addTab(readerTab, "Reader Management");
    tabWidget->addTab(borrowTab, "Borrow / Return");
    tabWidget->addTab(statisticsTab, "Statistics");

    setCentralWidget(tabWidget);
}