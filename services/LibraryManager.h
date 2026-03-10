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

    // Book - console
    void addBook();
    void showAllBooks() const;
    void findBookById() const;
    void findBookByTitle() const;
    void updateBook();
    void deleteBook();

    // Reader - console
    void addReader();
    void showAllReaders() const;
    void findReaderById() const;
    void updateReader();
    void deleteReader();

    // Borrow / Return - console
    void borrowBook();
    void returnBook();
    void showAllBorrowRecords() const;

    // Statistics - console
    void showGeneralStatistics() const;
    void showBorrowedBooks() const;
    void showOutOfStockBooks() const;
    void statisticsMenu() const;

    // Menu - console
    void bookMenu();
    void readerMenu();
    void borrowMenu();

    // =========================
    // GUI API
    // =========================

    const vector<Book>& getBooks() const {
        return books;
    }

    const vector<Reader>& getReaders() const {
        return readers;
    }

    const vector<BorrowRecord>& getBorrowRecords() const {
        return records;
    }

    bool addBookGUI(const Book& book) {
        if (findBookIndexById(book.getBookId()) != -1) return false;
        books.push_back(book);
        saveBooks();
        return true;
    }

    bool updateBookGUI(const string& bookId, const Book& updatedBook) {
        int index = findBookIndexById(bookId);
        if (index == -1) return false;

        if (bookId != updatedBook.getBookId()) {
            if (findBookIndexById(updatedBook.getBookId()) != -1) return false;
        }

        books[index] = updatedBook;
        saveBooks();
        return true;
    }

    bool deleteBookGUI(const string& bookId) {
        int index = findBookIndexById(bookId);
        if (index == -1) return false;

        for (const auto& record : records) {
            if (record.getBookId() == bookId && record.getStatus() == "Borrowing") {
                return false;
            }
        }

        books.erase(books.begin() + index);
        saveBooks();
        return true;
    }

    bool addReaderGUI(const Reader& reader) {
        if (findReaderIndexById(reader.getReaderId()) != -1) return false;
        readers.push_back(reader);
        saveReaders();
        return true;
    }

    bool updateReaderGUI(const string& readerId, const Reader& updatedReader) {
        int index = findReaderIndexById(readerId);
        if (index == -1) return false;

        if (readerId != updatedReader.getReaderId()) {
            if (findReaderIndexById(updatedReader.getReaderId()) != -1) return false;
        }

        readers[index] = updatedReader;
        saveReaders();
        return true;
    }

    bool deleteReaderGUI(const string& readerId) {
        int index = findReaderIndexById(readerId);
        if (index == -1) return false;

        for (const auto& record : records) {
            if (record.getReaderId() == readerId && record.getStatus() == "Borrowing") {
                return false;
            }
        }

        readers.erase(readers.begin() + index);
        saveReaders();
        return true;
    }

    bool borrowBookGUI(const string& readerId, const string& bookId, const string& borrowDate) {
        int readerIndex = findReaderIndexById(readerId);
        int bookIndex = findBookIndexById(bookId);

        if (readerIndex == -1 || bookIndex == -1) return false;
        if (books[bookIndex].getAvailable() <= 0) return false;

        string newRecordId = "BR" + to_string(records.size() + 1);
        while (findBorrowRecordIndexById(newRecordId) != -1) {
            newRecordId = "BR" + to_string(records.size() + 1 + rand() % 1000);
        }

        records.push_back(BorrowRecord(
            newRecordId,
            readerId,
            bookId,
            borrowDate,
            "",
            "Borrowing"
        ));

        books[bookIndex].setAvailable(books[bookIndex].getAvailable() - 1);

        saveBorrowRecords();
        saveBooks();
        return true;
    }

    bool returnBookGUI(const string& readerId, const string& bookId, const string& returnDate) {
        int recordIndex = -1;

        for (int i = 0; i < static_cast<int>(records.size()); ++i) {
            if (records[i].getReaderId() == readerId &&
                records[i].getBookId() == bookId &&
                records[i].getStatus() == "Borrowing") {
                recordIndex = i;
                break;
            }
        }

        if (recordIndex == -1) return false;

        int bookIndex = findBookIndexById(bookId);
        if (bookIndex != -1) {
            books[bookIndex].setAvailable(books[bookIndex].getAvailable() + 1);
        }

        records[recordIndex].setReturnDate(returnDate);
        records[recordIndex].setStatus("Returned");

        saveBorrowRecords();
        saveBooks();
        return true;
    }

    vector<Book> getOutOfStockBooksGUI() const {
        vector<Book> result;
        for (const auto& book : books) {
            if (book.getAvailable() <= 0) {
                result.push_back(book);
            }
        }
        return result;
    }

    vector<BorrowRecord> getBorrowingRecordsGUI() const {
        vector<BorrowRecord> result;
        for (const auto& record : records) {
            if (record.getStatus() == "Borrowing") {
                result.push_back(record);
            }
        }
        return result;
    }

    int getTotalBooksCountGUI() const {
        return static_cast<int>(books.size());
    }

    int getTotalReadersCountGUI() const {
        return static_cast<int>(readers.size());
    }

    int getBorrowingCountGUI() const {
        int count = 0;
        for (const auto& record : records) {
            if (record.getStatus() == "Borrowing") {
                ++count;
            }
        }
        return count;
    }

    string getBookTitleByIdGUI(const string& bookId) const {
        int index = findBookIndexById(bookId);
        if (index == -1) return "";
        return books[index].getTitle();
    }

    string getBookAuthorByIdGUI(const string& bookId) const {
        int index = findBookIndexById(bookId);
        if (index == -1) return "";
        return books[index].getAuthor();
    }

    string getReaderNameByIdGUI(const string& readerId) const {
        int index = findReaderIndexById(readerId);
        if (index == -1) return "";
        return readers[index].getName();
    }
};

#endif