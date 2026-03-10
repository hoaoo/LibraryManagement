#ifndef STATISTICSTAB_H
#define STATISTICSTAB_H

#include <QWidget>
#include "../services/LibraryManager.h"

class QLabel;
class QTableWidget;
class QPushButton;

class StatisticsTab : public QWidget {
    Q_OBJECT

public:
    explicit StatisticsTab(LibraryManager& manager, QWidget *parent = nullptr);

private slots:
    void onRefreshStatistics();

private:
    LibraryManager& manager;

    QLabel *totalBooksLabel;
    QLabel *totalReadersLabel;
    QLabel *borrowingBooksLabel;
    QLabel *outOfStockBooksLabel;

    QTableWidget *borrowingTable;
    QTableWidget *outOfStockTable;
    QPushButton *refreshButton;

    void setupUi();
    void loadStatistics();
};

#endif