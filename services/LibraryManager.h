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

public:
    LibraryManager();

    void loadBooks();
    void saveBooks() const;

    void loadReaders();
    void saveReaders() const;

    // Book management
    void addBook();
    void showAllBooks() const;
    void findBookById() const;
    void findBookByTitle() const;
    void updateBook();
    void deleteBook();

    // Reader management
    void addReader();
    void showAllReaders() const;
    void findReaderById() const;
    void updateReader();
    void deleteReader();

    // Menu
    void bookMenu();
    void readerMenu();
};

#endif