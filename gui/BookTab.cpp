#include "BookTab.h"

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

BookTab::BookTab(LibraryManager& manager, QWidget *parent)
    : QWidget(parent), manager(manager) {
    setupUi();
    loadBooks();
}

void BookTab::setupUi() {
    auto *mainLayout = new QVBoxLayout(this);

    auto *topLayout = new QHBoxLayout();
    auto *buttonLayout = new QHBoxLayout();

    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search books by ID, title, author...");

    addButton = new QPushButton("Add", this);
    editButton = new QPushButton("Edit", this);
    deleteButton = new QPushButton("Delete", this);
    refreshButton = new QPushButton("Refresh", this);

    topLayout->addWidget(new QLabel("Search:", this));
    topLayout->addWidget(searchEdit);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addStretch();

    bookTable = new QTableWidget(this);
    bookTable->setColumnCount(6);
    bookTable->setHorizontalHeaderLabels({
        "ID", "Title", "Author", "Category", "Quantity", "Available"
    });
    bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    bookTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    bookTable->setSelectionMode(QAbstractItemView::SingleSelection);
    bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bookTable->verticalHeader()->setVisible(false);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(bookTable);

    connect(addButton, &QPushButton::clicked, this, &BookTab::onAddBook);
    connect(editButton, &QPushButton::clicked, this, &BookTab::onEditBook);
    connect(deleteButton, &QPushButton::clicked, this, &BookTab::onDeleteBook);
    connect(refreshButton, &QPushButton::clicked, this, &BookTab::onRefreshBooks);
    connect(searchEdit, &QLineEdit::textChanged, this, &BookTab::onSearchTextChanged);
}

void BookTab::loadBooks() {
    bookTable->setRowCount(0);

    const auto& books = manager.getBooks();
    for (int i = 0; i < static_cast<int>(books.size()); ++i) {
        bookTable->insertRow(i);
        bookTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(books[i].getBookId())));
        bookTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(books[i].getTitle())));
        bookTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(books[i].getAuthor())));
        bookTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(books[i].getCategory())));
        bookTable->setItem(i, 4, new QTableWidgetItem(QString::number(books[i].getQuantity())));
        bookTable->setItem(i, 5, new QTableWidgetItem(QString::number(books[i].getAvailable())));
    }
}

void BookTab::filterBooks(const QString &keyword) {
    for (int row = 0; row < bookTable->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < bookTable->columnCount(); ++col) {
            auto *item = bookTable->item(row, col);
            if (item && item->text().contains(keyword, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        bookTable->setRowHidden(row, !match);
    }
}

int BookTab::selectedRow() const {
    auto items = bookTable->selectionModel()->selectedRows();
    if (items.isEmpty()) return -1;
    return items.first().row();
}

void BookTab::onAddBook() {
    bool ok;

    QString id = QInputDialog::getText(this, "Add Book", "Book ID:", QLineEdit::Normal, "", &ok);
    if (!ok || id.trimmed().isEmpty()) return;

    QString title = QInputDialog::getText(this, "Add Book", "Title:", QLineEdit::Normal, "", &ok);
    if (!ok || title.trimmed().isEmpty()) return;

    QString author = QInputDialog::getText(this, "Add Book", "Author:", QLineEdit::Normal, "", &ok);
    if (!ok || author.trimmed().isEmpty()) return;

    QString category = QInputDialog::getText(this, "Add Book", "Category:", QLineEdit::Normal, "", &ok);
    if (!ok || category.trimmed().isEmpty()) return;

    int quantity = QInputDialog::getInt(this, "Add Book", "Quantity:", 1, 1, 100000, 1, &ok);
    if (!ok) return;

    Book book(
        id.trimmed().toStdString(),
        title.trimmed().toStdString(),
        author.trimmed().toStdString(),
        category.trimmed().toStdString(),
        quantity,
        quantity
    );

    if (!manager.addBookGUI(book)) {
        QMessageBox::warning(this, "Add Book", "Không thể thêm sách. Có thể mã sách đã tồn tại.");
        return;
    }

    loadBooks();
    QMessageBox::information(this, "Add Book", "Thêm sách thành công.");
}

void BookTab::onEditBook() {
    int row = selectedRow();
    if (row < 0) {
        QMessageBox::warning(this, "Edit Book", "Vui lòng chọn một sách để sửa.");
        return;
    }

    QString oldId = bookTable->item(row, 0)->text();
    QString oldTitle = bookTable->item(row, 1)->text();
    QString oldAuthor = bookTable->item(row, 2)->text();
    QString oldCategory = bookTable->item(row, 3)->text();
    int oldQuantity = bookTable->item(row, 4)->text().toInt();
    int oldAvailable = bookTable->item(row, 5)->text().toInt();

    bool ok;

    QString newId = QInputDialog::getText(this, "Edit Book", "Book ID:", QLineEdit::Normal, oldId, &ok);
    if (!ok || newId.trimmed().isEmpty()) return;

    QString newTitle = QInputDialog::getText(this, "Edit Book", "Title:", QLineEdit::Normal, oldTitle, &ok);
    if (!ok || newTitle.trimmed().isEmpty()) return;

    QString newAuthor = QInputDialog::getText(this, "Edit Book", "Author:", QLineEdit::Normal, oldAuthor, &ok);
    if (!ok || newAuthor.trimmed().isEmpty()) return;

    QString newCategory = QInputDialog::getText(this, "Edit Book", "Category:", QLineEdit::Normal, oldCategory, &ok);
    if (!ok || newCategory.trimmed().isEmpty()) return;

    int newQuantity = QInputDialog::getInt(this, "Edit Book", "Quantity:", oldQuantity, 1, 100000, 1, &ok);
    if (!ok) return;

    if (oldAvailable > newQuantity) {
        QMessageBox::warning(this, "Edit Book", "Quantity mới không được nhỏ hơn số lượng currently available/balance logic.");
        return;
    }

    Book updatedBook(
        newId.trimmed().toStdString(),
        newTitle.trimmed().toStdString(),
        newAuthor.trimmed().toStdString(),
        newCategory.trimmed().toStdString(),
        newQuantity,
        oldAvailable
    );

    if (!manager.updateBookGUI(oldId.toStdString(), updatedBook)) {
        QMessageBox::warning(this, "Edit Book", "Không thể cập nhật sách.");
        return;
    }

    loadBooks();
    QMessageBox::information(this, "Edit Book", "Cập nhật sách thành công.");
}

void BookTab::onDeleteBook() {
    int row = selectedRow();
    if (row < 0) {
        QMessageBox::warning(this, "Delete Book", "Vui lòng chọn một sách để xóa.");
        return;
    }

    QString bookId = bookTable->item(row, 0)->text();

    auto reply = QMessageBox::question(this, "Delete Book", "Bạn có chắc muốn xóa sách đã chọn?");
    if (reply != QMessageBox::Yes) return;

    if (!manager.deleteBookGUI(bookId.toStdString())) {
        QMessageBox::warning(this, "Delete Book", "Không thể xóa sách. Có thể sách đang được mượn.");
        return;
    }

    loadBooks();
    QMessageBox::information(this, "Delete Book", "Xóa sách thành công.");
}

void BookTab::onRefreshBooks() {
    manager.loadBooks();
    loadBooks();
}

void BookTab::onSearchTextChanged(const QString &text) {
    filterBooks(text);
}