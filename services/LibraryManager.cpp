#include "LibraryManager.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

LibraryManager::LibraryManager() {}

int LibraryManager::findBookIndexById(const string& bookId) const {
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].getBookId() == bookId) {
            return i;
        }
    }
    return -1;
}

void LibraryManager::addBook() {
    string id, title, author, category;
    int quantity;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n===== THEM SACH =====\n";

    cout << "Nhap ma sach: ";
    getline(cin, id);

    if (id.empty()) {
        cout << "Ma sach khong duoc de trong.\n";
        return;
    }

    if (findBookIndexById(id) != -1) {
        cout << "Ma sach da ton tai.\n";
        return;
    }

    cout << "Nhap ten sach: ";
    getline(cin, title);

    cout << "Nhap tac gia: ";
    getline(cin, author);

    cout << "Nhap the loai: ";
    getline(cin, category);

    cout << "Nhap so luong: ";
    cin >> quantity;

    if (cin.fail() || quantity < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "So luong khong hop le.\n";
        return;
    }

    Book newBook(id, title, author, category, quantity, quantity);
    books.push_back(newBook);

    cout << "Them sach thanh cong.\n";
}

void LibraryManager::showAllBooks() const {
    cout << "\n===== DANH SACH SACH =====\n";

    if (books.empty()) {
        cout << "Chua co sach nao trong thu vien.\n";
        return;
    }

    cout << left
         << setw(10) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(25) << "Tac gia"
         << setw(20) << "The loai"
         << setw(10) << "Tong"
         << setw(10) << "Con lai"
         << endl;

    cout << string(105, '-') << endl;

    for (const auto& book : books) {
        book.display();
    }
}

void LibraryManager::findBookById() const {
    if (books.empty()) {
        cout << "Danh sach sach dang rong.\n";
        return;
    }

    string id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNhap ma sach can tim: ";
    getline(cin, id);

    int index = findBookIndexById(id);
    if (index == -1) {
        cout << "Khong tim thay sach co ma: " << id << endl;
        return;
    }

    cout << "\nTim thay sach:\n";
    cout << left
         << setw(10) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(25) << "Tac gia"
         << setw(20) << "The loai"
         << setw(10) << "Tong"
         << setw(10) << "Con lai"
         << endl;
    cout << string(105, '-') << endl;
    books[index].display();
}

void LibraryManager::findBookByTitle() const {
    if (books.empty()) {
        cout << "Danh sach sach dang rong.\n";
        return;
    }

    string keyword;
    bool found = false;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNhap ten sach can tim: ";
    getline(cin, keyword);

    cout << "\n===== KET QUA TIM KIEM =====\n";
    cout << left
         << setw(10) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(25) << "Tac gia"
         << setw(20) << "The loai"
         << setw(10) << "Tong"
         << setw(10) << "Con lai"
         << endl;
    cout << string(105, '-') << endl;

    for (const auto& book : books) {
        if (book.getTitle().find(keyword) != string::npos) {
            book.display();
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay sach phu hop.\n";
    }
}

void LibraryManager::updateBook() {
    if (books.empty()) {
        cout << "Danh sach sach dang rong.\n";
        return;
    }

    string id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNhap ma sach can sua: ";
    getline(cin, id);

    int index = findBookIndexById(id);
    if (index == -1) {
        cout << "Khong tim thay sach co ma: " << id << endl;
        return;
    }

    string title, author, category;
    int quantity;

    cout << "Nhap ten sach moi: ";
    getline(cin, title);

    cout << "Nhap tac gia moi: ";
    getline(cin, author);

    cout << "Nhap the loai moi: ";
    getline(cin, category);

    cout << "Nhap tong so luong moi: ";
    cin >> quantity;

    if (cin.fail() || quantity < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "So luong khong hop le.\n";
        return;
    }

    int borrowed = books[index].getQuantity() - books[index].getAvailable();
    if (quantity < borrowed) {
        cout << "Khong the giam tong so luong nho hon so sach dang duoc muon (" << borrowed << ").\n";
        return;
    }

    books[index].setTitle(title);
    books[index].setAuthor(author);
    books[index].setCategory(category);
    books[index].setQuantity(quantity);
    books[index].setAvailable(quantity - borrowed);

    cout << "Cap nhat sach thanh cong.\n";
}

void LibraryManager::deleteBook() {
    if (books.empty()) {
        cout << "Danh sach sach dang rong.\n";
        return;
    }

    string id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNhap ma sach can xoa: ";
    getline(cin, id);

    int index = findBookIndexById(id);
    if (index == -1) {
        cout << "Khong tim thay sach co ma: " << id << endl;
        return;
    }

    if (books[index].getAvailable() != books[index].getQuantity()) {
        cout << "Khong the xoa sach nay vi dang co sach duoc muon.\n";
        return;
    }

    books.erase(books.begin() + index);
    cout << "Xoa sach thanh cong.\n";
}

void LibraryManager::bookMenu() {
    int choice;

    do {
        cout << "\n===== QUAN LY SACH =====\n";
        cout << "1. Them sach\n";
        cout << "2. Hien thi danh sach sach\n";
        cout << "3. Tim sach theo ma\n";
        cout << "4. Tim sach theo ten\n";
        cout << "5. Sua thong tin sach\n";
        cout << "6. Xoa sach\n";
        cout << "0. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap so hop le.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                showAllBooks();
                break;
            case 3:
                findBookById();
                break;
            case 4:
                findBookByTitle();
                break;
            case 5:
                updateBook();
                break;
            case 6:
                deleteBook();
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}