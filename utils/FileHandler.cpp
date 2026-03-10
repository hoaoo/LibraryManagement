#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<Book> FileHandler::loadBooksFromFile(const string& filename) {
    vector<Book> books;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the mo file " << filename << ". Se tao moi khi luu du lieu.\n";
        return books;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string bookId, title, author, category, quantityStr, availableStr;

        getline(ss, bookId, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, quantityStr, '|');
        getline(ss, availableStr, '|');

        int quantity = stoi(quantityStr);
        int available = stoi(availableStr);

        books.emplace_back(bookId, title, author, category, quantity, available);
    }

    file.close();
    return books;
}

void FileHandler::saveBooksToFile(const string& filename, const vector<Book>& books) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the ghi file " << filename << endl;
        return;
    }

    for (const auto& book : books) {
        file << book.getBookId() << "|"
             << book.getTitle() << "|"
             << book.getAuthor() << "|"
             << book.getCategory() << "|"
             << book.getQuantity() << "|"
             << book.getAvailable() << "\n";
    }

    file.close();
}

vector<Reader> FileHandler::loadReadersFromFile(const string& filename) {
    vector<Reader> readers;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the mo file " << filename << ". Se tao moi khi luu du lieu.\n";
        return readers;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string readerId, name, phone, email;

        getline(ss, readerId, '|');
        getline(ss, name, '|');
        getline(ss, phone, '|');
        getline(ss, email, '|');

        readers.emplace_back(readerId, name, phone, email);
    }

    file.close();
    return readers;
}

void FileHandler::saveReadersToFile(const string& filename, const vector<Reader>& readers) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the ghi file " << filename << endl;
        return;
    }

    for (const auto& reader : readers) {
        file << reader.getReaderId() << "|"
             << reader.getName() << "|"
             << reader.getPhone() << "|"
             << reader.getEmail() << "\n";
    }

    file.close();

}
vector<BorrowRecord> FileHandler::loadBorrowRecordsFromFile(const string& filename) {
    vector<BorrowRecord> records;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the mo file " << filename << ". Se tao moi khi luu du lieu.\n";
        return records;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string recordId, readerId, bookId, borrowDate, returnDate, status;

        getline(ss, recordId, '|');
        getline(ss, readerId, '|');
        getline(ss, bookId, '|');
        getline(ss, borrowDate, '|');
        getline(ss, returnDate, '|');
        getline(ss, status, '|');

        records.emplace_back(recordId, readerId, bookId, borrowDate, returnDate, status);
    }

    file.close();
    return records;
}

void FileHandler::saveBorrowRecordsToFile(const string& filename, const vector<BorrowRecord>& records) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the ghi file " << filename << endl;
        return;
    }

    for (const auto& record : records) {
        file << record.getRecordId() << "|"
             << record.getReaderId() << "|"
             << record.getBookId() << "|"
             << record.getBorrowDate() << "|"
             << record.getReturnDate() << "|"
             << record.getStatus() << "\n";
    }

    file.close();
}