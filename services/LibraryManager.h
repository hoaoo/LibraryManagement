#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <vector>
#include <string>
#include "../models/Book.h"
#include "../models/Reader.h"
#include "../models/BorrowRecord.h"

using namespace std;

class LibraryManager {
private:
    vector<Book> books;
    vector<Reader> readers;
    vector<BorrowRecord> records;

    int findBookIndexById(const string& bookId) const;
    int findReaderIndexById(const string& readerId) const;
    int findBorrowRecordIndexById(const string& recordId) const;

public:
    LibraryManager();

    void loadBooks();
    void saveBooks() const;

    void loadReaders();
    void saveReaders() const;

    void loadBorrowRecords();
    void saveBorrowRecords() const;

    // Book
    void addBook();
    void showAllBooks() const;
    void findBookById() const;
    void findBookByTitle() const;
    void updateBook();
    void deleteBook();

    // Reader
    void addReader();
    void showAllReaders() const;
    void findReaderById() const;
    void updateReader();
    void deleteReader();

    // Borrow / Return
    void borrowBook();
    void returnBook();
    void showAllBorrowRecords() const;

    // Statistics
    void showGeneralStatistics() const;
    void showBorrowedBooks() const;
    void showOutOfStockBooks() const;
    void statisticsMenu() const;

    // Menu
    void bookMenu();
    void readerMenu();
    void borrowMenu();
};

#endif