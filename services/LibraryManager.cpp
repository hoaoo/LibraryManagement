#include "LibraryManager.h"
#include "../utils/FileHandler.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

LibraryManager::LibraryManager() {
    loadBooks();
    loadReaders();
    loadBorrowRecords();
}
void LibraryManager::loadBorrowRecords() {
    records = FileHandler::loadBorrowRecordsFromFile("../data/borrows.txt");
}

void LibraryManager::saveBorrowRecords() const {
    FileHandler::saveBorrowRecordsToFile("../data/borrows.txt", records);
}
void LibraryManager::loadBooks() {
    books = FileHandler::loadBooksFromFile("../data/books.txt");
}

void LibraryManager::saveBooks() const {
    FileHandler::saveBooksToFile("../data/books.txt", books);
}

void LibraryManager::loadReaders() {
    readers = FileHandler::loadReadersFromFile("../data/readers.txt");
}

void LibraryManager::saveReaders() const {
    FileHandler::saveReadersToFile("../data/readers.txt", readers);
}
int LibraryManager::findBorrowRecordIndexById(const string& recordId) const {
    for (int i = 0; i < (int)records.size(); i++) {
        if (records[i].getRecordId() == recordId) {
            return i;
        }
    }
    return -1;
}
int LibraryManager::findBookIndexById(const string& bookId) const {
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].getBookId() == bookId) {
            return i;
        }
    }
    return -1;
}

int LibraryManager::findReaderIndexById(const string& readerId) const {
    for (int i = 0; i < (int)readers.size(); i++) {
        if (readers[i].getReaderId() == readerId) {
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

    books.emplace_back(id, title, author, category, quantity, quantity);
    saveBooks();
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

    saveBooks();
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
    saveBooks();

    cout << "Xoa sach thanh cong.\n";
}

void LibraryManager::addReader() {
    string id, name, phone, email;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n===== THEM DOC GIA =====\n";

    cout << "Nhap ma doc gia: ";
    getline(cin, id);

    if (id.empty()) {
        cout << "Ma doc gia khong duoc de trong.\n";
        return;
    }

    if (findReaderIndexById(id) != -1) {
        cout << "Ma doc gia da ton tai.\n";
        return;
    }

    cout << "Nhap ho ten: ";
    getline(cin, name);

    cout << "Nhap so dien thoai: ";
    getline(cin, phone);

    cout << "Nhap email: ";
    getline(cin, email);

    readers.emplace_back(id, name, phone, email);
    saveReaders();

    cout << "Them doc gia thanh cong.\n";
}

void LibraryManager::showAllReaders() const {
    cout << "\n===== DANH SACH DOC GIA =====\n";

    if (readers.empty()) {
        cout << "Chua co doc gia nao.\n";
        return;
    }

    cout << left
         << setw(12) << "Ma DG"
         << setw(30) << "Ho ten"
         << setw(18) << "So dien thoai"
         << setw(30) << "Email"
         << endl;

    cout << string(90, '-') << endl;

    for (const auto& reader : readers) {
        reader.display();
    }
}

void LibraryManager::findReaderById() const {
    if (readers.empty()) {
        cout << "Danh sach doc gia dang rong.\n";
        return;
    }

    string id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNhap ma doc gia can tim: ";
    getline(cin, id);

    int index = findReaderIndexById(id);
    if (index == -1) {
        cout << "Khong tim thay doc gia co ma: " << id << endl;
        return;
    }

    cout << "\nTim thay doc gia:\n";
    cout << left
         << setw(12) << "Ma DG"
         << setw(30) << "Ho ten"
         << setw(18) << "So dien thoai"
         << setw(30) << "Email"
         << endl;

    cout << string(90, '-') << endl;
    readers[index].display();
}

void LibraryManager::updateReader() {
    if (readers.empty()) {
        cout << "Danh sach doc gia dang rong.\n";
        return;
    }

    string id, name, phone, email;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNhap ma doc gia can sua: ";
    getline(cin, id);

    int index = findReaderIndexById(id);
    if (index == -1) {
        cout << "Khong tim thay doc gia co ma: " << id << endl;
        return;
    }

    cout << "Nhap ho ten moi: ";
    getline(cin, name);

    cout << "Nhap so dien thoai moi: ";
    getline(cin, phone);

    cout << "Nhap email moi: ";
    getline(cin, email);

    readers[index].setName(name);
    readers[index].setPhone(phone);
    readers[index].setEmail(email);

    saveReaders();
    cout << "Cap nhat doc gia thanh cong.\n";
}

void LibraryManager::deleteReader() {
    if (readers.empty()) {
        cout << "Danh sach doc gia dang rong.\n";
        return;
    }

    string id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNhap ma doc gia can xoa: ";
    getline(cin, id);

    int index = findReaderIndexById(id);
    if (index == -1) {
        cout << "Khong tim thay doc gia co ma: " << id << endl;
        return;
    }

    readers.erase(readers.begin() + index);
    saveReaders();

    cout << "Xoa doc gia thanh cong.\n";
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
        cout << "7. Tai lai danh sach sach tu file\n";
        cout << "8. Luu danh sach sach vao file\n";
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
            case 1: addBook(); break;
            case 2: showAllBooks(); break;
            case 3: findBookById(); break;
            case 4: findBookByTitle(); break;
            case 5: updateBook(); break;
            case 6: deleteBook(); break;
            case 7:
                loadBooks();
                cout << "Da tai lai du lieu sach tu file.\n";
                break;
            case 8:
                saveBooks();
                cout << "Da luu du lieu sach vao file.\n";
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}

void LibraryManager::readerMenu() {
    int choice;

    do {
        cout << "\n===== QUAN LY DOC GIA =====\n";
        cout << "1. Them doc gia\n";
        cout << "2. Hien thi danh sach doc gia\n";
        cout << "3. Tim doc gia theo ma\n";
        cout << "4. Sua thong tin doc gia\n";
        cout << "5. Xoa doc gia\n";
        cout << "6. Tai lai danh sach doc gia tu file\n";
        cout << "7. Luu danh sach doc gia vao file\n";
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
            case 1: addReader(); break;
            case 2: showAllReaders(); break;
            case 3: findReaderById(); break;
            case 4: updateReader(); break;
            case 5: deleteReader(); break;
            case 6:
                loadReaders();
                cout << "Da tai lai du lieu doc gia tu file.\n";
                break;
            case 7:
                saveReaders();
                cout << "Da luu du lieu doc gia vao file.\n";
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}
void LibraryManager::borrowBook() {
    if (books.empty()) {
        cout << "Khong co sach trong thu vien.\n";
        return;
    }

    if (readers.empty()) {
        cout << "Khong co doc gia nao.\n";
        return;
    }

    string recordId, readerId, bookId, borrowDate;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n===== MUON SACH =====\n";

    cout << "Nhap ma phieu muon: ";
    getline(cin, recordId);

    if (recordId.empty()) {
        cout << "Ma phieu muon khong duoc de trong.\n";
        return;
    }

    if (findBorrowRecordIndexById(recordId) != -1) {
        cout << "Ma phieu muon da ton tai.\n";
        return;
    }

    cout << "Nhap ma doc gia: ";
    getline(cin, readerId);

    int readerIndex = findReaderIndexById(readerId);
    if (readerIndex == -1) {
        cout << "Khong tim thay doc gia.\n";
        return;
    }

    cout << "Nhap ma sach: ";
    getline(cin, bookId);

    int bookIndex = findBookIndexById(bookId);
    if (bookIndex == -1) {
        cout << "Khong tim thay sach.\n";
        return;
    }

    if (books[bookIndex].getAvailable() <= 0) {
        cout << "Sach da het, khong the muon.\n";
        return;
    }

    cout << "Nhap ngay muon (YYYY-MM-DD): ";
    getline(cin, borrowDate);

    records.emplace_back(recordId, readerId, bookId, borrowDate, "", "Borrowed");

    books[bookIndex].setAvailable(books[bookIndex].getAvailable() - 1);

    saveBorrowRecords();
    saveBooks();

    cout << "Muon sach thanh cong.\n";
}
void LibraryManager::returnBook() {
    if (records.empty()) {
        cout << "Chua co phieu muon nao.\n";
        return;
    }

    string recordId, returnDate;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n===== TRA SACH =====\n";
    cout << "Nhap ma phieu muon: ";
    getline(cin, recordId);

    int recordIndex = findBorrowRecordIndexById(recordId);
    if (recordIndex == -1) {
        cout << "Khong tim thay phieu muon.\n";
        return;
    }

    if (records[recordIndex].getStatus() == "Returned") {
        cout << "Phieu nay da duoc tra sach roi.\n";
        return;
    }

    cout << "Nhap ngay tra (YYYY-MM-DD): ";
    getline(cin, returnDate);

    string bookId = records[recordIndex].getBookId();
    int bookIndex = findBookIndexById(bookId);

    if (bookIndex != -1) {
        books[bookIndex].setAvailable(books[bookIndex].getAvailable() + 1);
    }

    records[recordIndex].setReturnDate(returnDate);
    records[recordIndex].setStatus("Returned");

    saveBorrowRecords();
    saveBooks();

    cout << "Tra sach thanh cong.\n";
}
void LibraryManager::showAllBorrowRecords() const {
    cout << "\n===== DANH SACH PHIEU MUON / TRA =====\n";

    if (records.empty()) {
        cout << "Chua co phieu muon nao.\n";
        return;
    }

    cout << left
         << setw(12) << "Ma phieu"
         << setw(12) << "Ma DG"
         << setw(12) << "Ma sach"
         << setw(15) << "Ngay muon"
         << setw(15) << "Ngay tra"
         << setw(12) << "Trang thai"
         << endl;

    cout << string(78, '-') << endl;

    for (const auto& record : records) {
        record.display();
    }
}
void LibraryManager::borrowMenu() {
    int choice;

    do {
        cout << "\n===== MUON / TRA SACH =====\n";
        cout << "1. Muon sach\n";
        cout << "2. Tra sach\n";
        cout << "3. Hien thi danh sach phieu muon/tra\n";
        cout << "4. Tai lai du lieu phieu muon tu file\n";
        cout << "5. Luu du lieu phieu muon vao file\n";
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
                borrowBook();
                break;
            case 2:
                returnBook();
                break;
            case 3:
                showAllBorrowRecords();
                break;
            case 4:
                loadBorrowRecords();
                cout << "Da tai lai du lieu phieu muon.\n";
                break;
            case 5:
                saveBorrowRecords();
                cout << "Da luu du lieu phieu muon.\n";
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}