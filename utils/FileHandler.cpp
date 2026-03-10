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
        if (line.empty()) {
            continue;
        }

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