#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <string>
using namespace std;

class BorrowRecord {
private:
    string recordId;
    string readerId;
    string bookId;
    string borrowDate;
    string returnDate;
    string status;

public:
    BorrowRecord();
    BorrowRecord(string recordId, string readerId, string bookId, string borrowDate, string returnDate, string status);

    string getRecordId() const;
    string getReaderId() const;
    string getBookId() const;
    string getBorrowDate() const;
    string getReturnDate() const;
    string getStatus() const;

    void setReturnDate(const string& returnDate);
    void setStatus(const string& status);

    void display() const;
};

#endif