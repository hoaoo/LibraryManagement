#include "Validator.h"
#include <iostream>
#include <limits>
#include <regex>

using namespace std;

int Validator::inputInt(const string& message, int minValue) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        // Nếu người dùng nhập sai kiểu dữ liệu
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap mot so hop le.\n";
            continue;
        }

        // Nếu số nhỏ hơn giá trị tối thiểu cho phép
        if (value < minValue) {
            cout << "Gia tri phai lon hon hoac bang " << minValue << ".\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Xóa ký tự xuống dòng còn sót lại
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

string Validator::inputNonEmptyString(const string& message) {
    string value;

    while (true) {
        cout << message;
        getline(cin, value);

        if (value.empty()) {
            cout << "Du lieu khong duoc de trong.\n";
            continue;
        }

        return value;
    }
}

bool Validator::isValidDateFormat(const string& date) {
    // Regex kiểm tra đúng dạng YYYY-MM-DD
    regex pattern("^\\d{4}-\\d{2}-\\d{2}$");
    return regex_match(date, pattern);
}

bool Validator::confirmAction(const string& message) {
    string choice;

    while (true) {
        cout << message << " (y/n): ";
        getline(cin, choice);

        if (choice == "y" || choice == "Y") {
            return true;
        }

        if (choice == "n" || choice == "N") {
            return false;
        }

        cout << "Vui long nhap y hoac n.\n";
    }
}