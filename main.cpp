#include <iostream>
#include "services/LibraryManager.h"
#include "utils/Validator.h"

using namespace std;

// Ham hien thi menu chinh
void showMainMenu() {
    cout << "\n========================================\n";
    cout << "        LIBRARY MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Quan ly sach\n";
    cout << "2. Quan ly doc gia\n";
    cout << "3. Muon / Tra sach\n";
    cout << "4. Thong ke\n";
    cout << "0. Thoat\n";
    cout << "----------------------------------------\n";
}

int main() {
    LibraryManager manager;
    int choice;

    do {
        showMainMenu();
        choice = Validator::inputInt("Nhap lua chon: ", 0);

        switch (choice) {
            case 1:
                manager.bookMenu();
                break;
            case 2:
                manager.readerMenu();
                break;
            case 3:
                manager.borrowMenu();
                break;
            case 4:
                manager.statisticsMenu();
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);

    return 0;
}