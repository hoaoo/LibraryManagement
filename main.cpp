#include <iostream>
#include "services/LibraryManager.h"

using namespace std;

void showMainMenu() {
    cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====" << endl;
    cout << "1. Quan ly sach" << endl;
    cout << "2. Quan ly doc gia" << endl;
    cout << "3. Muon sach" << endl;
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

        switch (choice) {
            case 1:
                manager.bookMenu();
                break;
            case 2:
                cout << "Chuc nang quan ly doc gia dang phat trien." << endl;
                break;
            case 3:
                cout << "Chuc nang muon sach dang phat trien." << endl;
                break;
            case 4:
                cout << "Chuc nang tra sach dang phat trien." << endl;
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