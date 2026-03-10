#include "LibraryManager.h"
#include "../utils/FileHandler.h"
#include "../utils/Validator.h"
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
    cout << "\n===== THEM SACH =====\n";

    // Nhap thong tin sach bang cac ham validator
    string id = Validator::inputNonEmptyString("Nhap ma sach: ");

    // Kiem tra trung ma sach
    if (findBookIndexById(id) != -1) {
        cout << "Ma sach da ton tai.\n";
        return;
    }

    string title = Validator::inputNonEmptyString("Nhap ten sach: ");
    string author = Validator::inputNonEmptyString("Nhap tac gia: ");
    string category = Validator::inputNonEmptyString("Nhap the loai: ");
    int quantity = Validator::inputInt("Nhap so luong: ", 0);

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

    string id = Validator::inputNonEmptyString("Nhap ma sach can tim: ");
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

    string keyword = Validator::inputNonEmptyString("Nhap ten sach can tim: ");
    bool found = false;

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

    cout << "\n===== SUA THONG TIN SACH =====\n";

    string id = Validator::inputNonEmptyString("Nhap ma sach can sua: ");
    int index = findBookIndexById(id);

    if (index == -1) {
        cout << "Khong tim thay sach co ma: " << id << endl;
        return;
    }

    string title = Validator::inputNonEmptyString("Nhap ten sach moi: ");
    string author = Validator::inputNonEmptyString("Nhap tac gia moi: ");
    string category = Validator::inputNonEmptyString("Nhap the loai moi: ");
    int quantity = Validator::inputInt("Nhap tong so luong moi: ", 0);

    // So sach dang duoc muon = tong - con lai
    int borrowed = books[index].getQuantity() - books[index].getAvailable();

    // Khong cho tong so luong moi nho hon so sach dang muon
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

    cout << "\n===== XOA SACH =====\n";

    string id = Validator::inputNonEmptyString("Nhap ma sach can xoa: ");
    int index = findBookIndexById(id);

    if (index == -1) {
        cout << "Khong tim thay sach co ma: " << id << endl;
        return;
    }

    // Khong cho xoa neu van con sach dang duoc muon
    if (books[index].getAvailable() != books[index].getQuantity()) {
        cout << "Khong the xoa sach nay vi dang co sach duoc muon.\n";
        return;
    }

    // Xac nhan truoc khi xoa
    if (!Validator::confirmAction("Ban co chac chan muon xoa sach nay khong")) {
        cout << "Da huy thao tac xoa sach.\n";
        return;
    }

    books.erase(books.begin() + index);
    saveBooks();

    cout << "Xoa sach thanh cong.\n";
}

void LibraryManager::addReader() {
    cout << "\n===== THEM DOC GIA =====\n";

    string id = Validator::inputNonEmptyString("Nhap ma doc gia: ");

    // Kiem tra trung ma doc gia
    if (findReaderIndexById(id) != -1) {
        cout << "Ma doc gia da ton tai.\n";
        return;
    }

    string name = Validator::inputNonEmptyString("Nhap ho ten: ");
    string phone = Validator::inputNonEmptyString("Nhap so dien thoai: ");
    string email = Validator::inputNonEmptyString("Nhap email: ");

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

    string id = Validator::inputNonEmptyString("Nhap ma doc gia can tim: ");
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

    cout << "\n===== SUA THONG TIN DOC GIA =====\n";

    string id = Validator::inputNonEmptyString("Nhap ma doc gia can sua: ");
    int index = findReaderIndexById(id);

    if (index == -1) {
        cout << "Khong tim thay doc gia co ma: " << id << endl;
        return;
    }

    string name = Validator::inputNonEmptyString("Nhap ho ten moi: ");
    string phone = Validator::inputNonEmptyString("Nhap so dien thoai moi: ");
    string email = Validator::inputNonEmptyString("Nhap email moi: ");

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

    cout << "\n===== XOA DOC GIA =====\n";

    string id = Validator::inputNonEmptyString("Nhap ma doc gia can xoa: ");
    int index = findReaderIndexById(id);

    if (index == -1) {
        cout << "Khong tim thay doc gia co ma: " << id << endl;
        return;
    }

    if (!Validator::confirmAction("Ban co chac chan muon xoa doc gia nay khong")) {
        cout << "Da huy thao tac xoa doc gia.\n";
        return;
    }

    readers.erase(readers.begin() + index);
    saveReaders();

    cout << "Xoa doc gia thanh cong.\n";
}

void LibraryManager::bookMenu() {
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "              QUAN LY SACH\n";
        cout << "========================================\n";
        cout << "1. Them sach\n";
        cout << "2. Hien thi danh sach sach\n";
        cout << "3. Tim sach theo ma\n";
        cout << "4. Tim sach theo ten\n";
        cout << "5. Sua thong tin sach\n";
        cout << "6. Xoa sach\n";
        cout << "7. Tai lai danh sach sach tu file\n";
        cout << "8. Luu danh sach sach vao file\n";
        cout << "0. Quay lai\n";
        cout << "----------------------------------------\n";

        choice = Validator::inputInt("Nhap lua chon: ", 0);

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
        cout << "\n========================================\n";
        cout << "             QUAN LY DOC GIA\n";
        cout << "========================================\n";
        cout << "1. Them doc gia\n";
        cout << "2. Hien thi danh sach doc gia\n";
        cout << "3. Tim doc gia theo ma\n";
        cout << "4. Sua thong tin doc gia\n";
        cout << "5. Xoa doc gia\n";
        cout << "6. Tai lai danh sach doc gia tu file\n";
        cout << "7. Luu danh sach doc gia vao file\n";
        cout << "0. Quay lai\n";
        cout << "----------------------------------------\n";

        choice = Validator::inputInt("Nhap lua chon: ", 0);

        switch (choice) {
            case 1:
                addReader();
                break;
            case 2:
                showAllReaders();
                break;
            case 3:
                findReaderById();
                break;
            case 4:
                updateReader();
                break;
            case 5:
                deleteReader();
                break;
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

    cout << "\n===== MUON SACH =====\n";

    string recordId = Validator::inputNonEmptyString("Nhap ma phieu muon: ");

    // Kiem tra trung ma phieu muon
    if (findBorrowRecordIndexById(recordId) != -1) {
        cout << "Ma phieu muon da ton tai.\n";
        return;
    }

    string readerId = Validator::inputNonEmptyString("Nhap ma doc gia: ");
    int readerIndex = findReaderIndexById(readerId);

    if (readerIndex == -1) {
        cout << "Khong tim thay doc gia.\n";
        return;
    }

    string bookId = Validator::inputNonEmptyString("Nhap ma sach: ");
    int bookIndex = findBookIndexById(bookId);

    if (bookIndex == -1) {
        cout << "Khong tim thay sach.\n";
        return;
    }

    if (books[bookIndex].getAvailable() <= 0) {
        cout << "Sach da het, khong the muon.\n";
        return;
    }

    string borrowDate = Validator::inputNonEmptyString("Nhap ngay muon (YYYY-MM-DD): ");

    if (!Validator::isValidDateFormat(borrowDate)) {
        cout << "Ngay muon khong dung dinh dang YYYY-MM-DD.\n";
        return;
    }

    // Tao phieu muon moi
    records.emplace_back(recordId, readerId, bookId, borrowDate, "", "Borrowed");

    // Giam so luong sach con lai
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

    cout << "\n===== TRA SACH =====\n";

    string recordId = Validator::inputNonEmptyString("Nhap ma phieu muon: ");
    int recordIndex = findBorrowRecordIndexById(recordId);

    if (recordIndex == -1) {
        cout << "Khong tim thay phieu muon.\n";
        return;
    }

    if (records[recordIndex].getStatus() == "Returned") {
        cout << "Phieu nay da duoc tra sach roi.\n";
        return;
    }

    string returnDate = Validator::inputNonEmptyString("Nhap ngay tra (YYYY-MM-DD): ");

    if (!Validator::isValidDateFormat(returnDate)) {
        cout << "Ngay tra khong dung dinh dang YYYY-MM-DD.\n";
        return;
    }

    string bookId = records[recordIndex].getBookId();
    int bookIndex = findBookIndexById(bookId);

    // Neu tim thay sach thi tang lai so luong con
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
        cout << "\n========================================\n";
        cout << "             MUON / TRA SACH\n";
        cout << "========================================\n";
        cout << "1. Muon sach\n";
        cout << "2. Tra sach\n";
        cout << "3. Hien thi danh sach phieu muon/tra\n";
        cout << "4. Tai lai du lieu phieu muon tu file\n";
        cout << "5. Luu du lieu phieu muon vao file\n";
        cout << "0. Quay lai\n";
        cout << "----------------------------------------\n";

        choice = Validator::inputInt("Nhap lua chon: ", 0);

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
void LibraryManager::showGeneralStatistics() const {
    int totalBookTitles = (int)books.size();
    int totalBookQuantity = 0;
    int totalAvailableBooks = 0;
    int totalBorrowedBooks = 0;

    for (const auto& book : books) {
        totalBookQuantity += book.getQuantity();
        totalAvailableBooks += book.getAvailable();
        totalBorrowedBooks += (book.getQuantity() - book.getAvailable());
    }

    int totalReaders = (int)readers.size();
    int totalBorrowRecords = (int)records.size();

    int borrowingRecords = 0;
    int returnedRecords = 0;

    for (const auto& record : records) {
        if (record.getStatus() == "Borrowed") {
            borrowingRecords++;
        } else if (record.getStatus() == "Returned") {
            returnedRecords++;
        }
    }

    cout << "\n===== THONG KE TONG QUAN =====\n";
    cout << "Tong so dau sach: " << totalBookTitles << endl;
    cout << "Tong so ban sach: " << totalBookQuantity << endl;
    cout << "So sach dang duoc muon: " << totalBorrowedBooks << endl;
    cout << "So sach con trong thu vien: " << totalAvailableBooks << endl;
    cout << "Tong so doc gia: " << totalReaders << endl;
    cout << "Tong so phieu muon: " << totalBorrowRecords << endl;
    cout << "So phieu dang muon: " << borrowingRecords << endl;
    cout << "So phieu da tra: " << returnedRecords << endl;
}
void LibraryManager::showBorrowedBooks() const {
    cout << "\n===== DANH SACH SACH DANG DUOC MUON =====\n";

    bool found = false;

    cout << left
         << setw(10) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(25) << "Tac gia"
         << setw(20) << "The loai"
         << setw(10) << "Tong"
         << setw(10) << "Con lai"
         << setw(12) << "Dang muon"
         << endl;

    cout << string(117, '-') << endl;

    for (const auto& book : books) {
        int borrowed = book.getQuantity() - book.getAvailable();
        if (borrowed > 0) {
            cout << left
                 << setw(10) << book.getBookId()
                 << setw(30) << book.getTitle()
                 << setw(25) << book.getAuthor()
                 << setw(20) << book.getCategory()
                 << setw(10) << book.getQuantity()
                 << setw(10) << book.getAvailable()
                 << setw(12) << borrowed
                 << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Khong co sach nao dang duoc muon.\n";
    }
}
void LibraryManager::statisticsMenu() const {
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "                THONG KE\n";
        cout << "========================================\n";
        cout << "1. Thong ke tong quan\n";
        cout << "2. Danh sach sach dang duoc muon\n";
        cout << "3. Danh sach sach da muon het\n";
        cout << "0. Quay lai\n";
        cout << "----------------------------------------\n";

        choice = Validator::inputInt("Nhap lua chon: ", 0);

        switch (choice) {
            case 1:
                showGeneralStatistics();
                break;
            case 2:
                showBorrowedBooks();
                break;
            case 3:
                showOutOfStockBooks();
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}
void LibraryManager::showOutOfStockBooks() const {
    cout << "\n===== DANH SACH SACH DA MUON HET =====\n";

    bool found = false;

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
        if (book.getAvailable() == 0) {
            book.display();
            found = true;
        }
    }

    if (!found) {
        cout << "Khong co sach nao bi muon het.\n";
    }
}