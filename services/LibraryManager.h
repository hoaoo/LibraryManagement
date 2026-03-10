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

public:
    LibraryManager();

    // Book management
    void addBook();
    void showAllBooks() const;
    void findBookById(const string& bookId) const;

    // Menu
    void bookMenu();
};

#endif