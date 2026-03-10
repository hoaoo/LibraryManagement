#include "BorrowRecord.h"
#include <iostream>
using namespace std;

BorrowRecord::BorrowRecord() {}

BorrowRecord::BorrowRecord(string recordId, string readerId, string bookId, string borrowDate, string returnDate, string status)
        : recordId(recordId), readerId(readerId), bookId(bookId), borrowDate(borrowDate), returnDate(returnDate), status(status) {}

string BorrowRecord::getRecordId() const { return recordId; }
string BorrowRecord::getReaderId() const { return readerId; }
string BorrowRecord::getBookId() const { return bookId; }
string BorrowRecord::getBorrowDate() const { return borrowDate; }
string BorrowRecord::getReturnDate() const { return returnDate; }
string BorrowRecord::getStatus() const { return status; }

void BorrowRecord::setReturnDate(const string& returnDate) { this->returnDate = returnDate; }
void BorrowRecord::setStatus(const string& status) { this->status = status; }

void BorrowRecord::display() const {
    cout << "Record ID: " << recordId << endl;
    cout << "Reader ID: " << readerId << endl;
    cout << "Book ID: " << bookId << endl;
    cout << "Borrow Date: " << borrowDate << endl;
    cout << "Return Date: " << returnDate << endl;
    cout << "Status: " << status << endl;
}