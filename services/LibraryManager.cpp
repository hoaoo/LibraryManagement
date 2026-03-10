#include "LibraryManager.h"
#include <iostream>

using namespace std;

LibraryManager::LibraryManager() {}

void LibraryManager::addBook() {
    string id, title, author, category;
    int quantity;

    cin.ignore();

    cout << "Nhap ma sach: ";
    getline(cin, id);

    cout << "Nhap ten sach: ";
    getline(cin, title);

    cout << "Nhap tac gia: ";
    getline(cin, author);

    cout << "Nhap the loai: ";
    getline(cin, category);

    cout << "Nhap so luong: ";
    cin >> quantity;

    Book newBook(id, title, author, category, quantity, quantity);
    books.push_back(newBook);

    cout << "Them sach thanh cong.\n";
}

void LibraryManager::showAllBooks() const {
    if (books.empty()) {
        cout << "Danh sach sach dang rong.\n";
        return;
    }

    cout << "\n===== DANH SACH SACH =====\n";
    for (const auto& book : books) {
        book.display();
        cout << "--------------------------\n";
    }
}

void LibraryManager::findBookById(const string& bookId) const {
    for (const auto& book : books) {
        if (book.getBookId() == bookId) {
            cout << "\nTim thay sach:\n";
            book.display();
            return;
        }
    }
    cout << "Khong tim thay sach co ma: " << bookId << endl;
}

void LibraryManager::bookMenu() {
    int choice;
    string bookId;

    do {
        cout << "\n===== QUAN LY SACH =====\n";
        cout << "1. Them sach\n";
        cout << "2. Hien thi danh sach sach\n";
        cout << "3. Tim sach theo ma\n";
        cout << "0. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                showAllBooks();
                break;
            case 3:
                cin.ignore();
                cout << "Nhap ma sach can tim: ";
                getline(cin, bookId);
                findBookById(bookId);
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}