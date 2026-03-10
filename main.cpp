#include <iostream>
#include "services/LibraryManager.h"

using namespace std;

void showMainMenu() {
    cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====" << endl;
    cout << "1. Quan ly sach" << endl;
    cout << "2. Quan ly doc gia" << endl;
    cout << "3. Muon / Tra sach" << endl;
    cout << "4. Tra sach" << endl;
    cout << "5. Thong ke" << endl;
    cout << "0. Thoat" << endl;
    cout << "Nhap lua chon: ";
}

int main() {
    LibraryManager manager;
    int choice;

    do {
        showMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Vui long nhap so hop le.\n";
            continue;
        }

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
                cout << "Chuc nang nay da duoc dua vao menu Muon / Tra sach." << endl;
                break;
            case 5:
                cout << "Chuc nang thong ke dang phat trien." << endl;
                break;
            case 0:
                cout << "Thoat chuong trinh." << endl;
                break;
            default:
                cout << "Lua chon khong hop le." << endl;
        }
    } while (choice != 0);

    return 0;
}