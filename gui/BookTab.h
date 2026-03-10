#ifndef BOOKTAB_H
#define BOOKTAB_H

#include <QWidget>
#include "../services/LibraryManager.h"

class QLineEdit;
class QPushButton;
class QTableWidget;

class BookTab : public QWidget {
    Q_OBJECT

public:
    explicit BookTab(LibraryManager& manager, QWidget *parent = nullptr);

private slots:
    void onAddBook();
    void onEditBook();
    void onDeleteBook();
    void onRefreshBooks();
    void onSearchTextChanged(const QString &text);

private:
    LibraryManager& manager;

    QLineEdit *searchEdit;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *refreshButton;
    QTableWidget *bookTable;

    void setupUi();
    void loadBooks();
    void filterBooks(const QString &keyword);
    int selectedRow() const;
};

#endif