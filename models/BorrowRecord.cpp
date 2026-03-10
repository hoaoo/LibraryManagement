#include "BorrowRecord.h"
#include <iostream>
#include <iomanip>

using namespace std;

BorrowRecord::BorrowRecord() {}

BorrowRecord::BorrowRecord(string recordId, string readerId, string bookId,
                           string borrowDate, string returnDate, string status)
        : recordId(recordId), readerId(readerId), bookId(bookId),
          borrowDate(borrowDate), returnDate(returnDate), status(status) {}

string BorrowRecord::getRecordId() const {
    return recordId;
}

string BorrowRecord::getReaderId() const {
    return readerId;
}

string BorrowRecord::getBookId() const {
    return bookId;
}

string BorrowRecord::getBorrowDate() const {
    return borrowDate;
}

string BorrowRecord::getReturnDate() const {
    return returnDate;
}

string BorrowRecord::getStatus() const {
    return status;
}

void BorrowRecord::setRecordId(const string& recordId) {
    this->recordId = recordId;
}

void BorrowRecord::setReaderId(const string& readerId) {
    this->readerId = readerId;
}

void BorrowRecord::setBookId(const string& bookId) {
    this->bookId = bookId;
}

void BorrowRecord::setBorrowDate(const string& borrowDate) {
    this->borrowDate = borrowDate;
}

void BorrowRecord::setReturnDate(const string& returnDate) {
    this->returnDate = returnDate;
}

void BorrowRecord::setStatus(const string& status) {
    this->status = status;
}

void BorrowRecord::display() const {
    cout << left
         << setw(12) << recordId
         << setw(12) << readerId
         << setw(12) << bookId
         << setw(15) << borrowDate
         << setw(15) << returnDate
         << setw(12) << status
         << endl;
}