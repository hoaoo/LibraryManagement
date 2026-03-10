#ifndef READER_H
#define READER_H

#include <string>

using namespace std;

class Reader {
private:
    string readerId;
    string name;
    string phone;
    string email;

public:
    Reader();
    Reader(string readerId, string name, string phone, string email);

    string getReaderId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;

    void setReaderId(const string& readerId);
    void setName(const string& name);
    void setPhone(const string& phone);
    void setEmail(const string& email);

    void display() const;
};

#endif