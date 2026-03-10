#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../services/LibraryManager.h"

class QTabWidget;
class BookTab;
class ReaderTab;
class BorrowTab;
class StatisticsTab;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    LibraryManager manager;

    QTabWidget *tabWidget;
    BookTab *bookTab;
    ReaderTab *readerTab;
    BorrowTab *borrowTab;
    StatisticsTab *statisticsTab;

    void setupUi();
};

#endif