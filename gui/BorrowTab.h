#ifndef BORROWTAB_H
#define BORROWTAB_H

#include <QWidget>
#include "../services/LibraryManager.h"

class QLineEdit;
class QPushButton;
class QTableWidget;
class QDateEdit;

class BorrowTab : public QWidget {
    Q_OBJECT

public:
    explicit BorrowTab(LibraryManager& manager, QWidget *parent = nullptr);

private slots:
    void onBorrowBook();
    void onReturnBook();
    void onRefreshHistory();

private:
    LibraryManager& manager;

    QLineEdit *readerIdEdit;
    QLineEdit *bookIdEdit;
    QDateEdit *borrowDateEdit;
    QPushButton *borrowButton;

    QLineEdit *returnReaderIdEdit;
    QLineEdit *returnBookIdEdit;
    QDateEdit *returnDateEdit;
    QPushButton *returnButton;

    QPushButton *refreshButton;
    QTableWidget *historyTable;

    void setupUi();
    void loadHistory();
};

#endif