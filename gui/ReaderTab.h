#ifndef READERTAB_H
#define READERTAB_H

#include <QWidget>
#include "../services/LibraryManager.h"

class QLineEdit;
class QPushButton;
class QTableWidget;

class ReaderTab : public QWidget {
    Q_OBJECT

public:
    explicit ReaderTab(LibraryManager& manager, QWidget *parent = nullptr);

private slots:
    void onAddReader();
    void onEditReader();
    void onDeleteReader();
    void onRefreshReaders();
    void onSearchTextChanged(const QString &text);

private:
    LibraryManager& manager;

    QLineEdit *searchEdit;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *refreshButton;
    QTableWidget *readerTable;

    void setupUi();
    void loadReaders();
    void filterReaders(const QString &keyword);
    int selectedRow() const;
};

#endif