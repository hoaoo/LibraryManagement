#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

using namespace std;

class Validator {
public:
    // Nhập số nguyên, bắt buộc >= minValue
    static int inputInt(const string& message, int minValue = 0);

    // Nhập chuỗi không được để trống
    static string inputNonEmptyString(const string& message);

    // Kiểm tra định dạng ngày YYYY-MM-DD
    static bool isValidDateFormat(const string& date);

    // Hỏi xác nhận y/n
    static bool confirmAction(const string& message);
};

#endif