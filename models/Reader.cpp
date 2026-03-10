#include "Reader.h"
#include <iostream>
using namespace std;

Reader::Reader() {}

Reader::Reader(string readerId, string name, string phone, string email)
        : readerId(readerId), name(name), phone(phone), email(email) {}

string Reader::getReaderId() const { return readerId; }
string Reader::getName() const { return name; }
string Reader::getPhone() const { return phone; }
string Reader::getEmail() const { return email; }

void Reader::setName(const string& name) { this->name = name; }
void Reader::setPhone(const string& phone) { this->phone = phone; }
void Reader::setEmail(const string& email) { this->email = email; }

void Reader::display() const {
    cout << "Reader ID: " << readerId << endl;
    cout << "Name: " << name << endl;
    cout << "Phone: " << phone << endl;
    cout << "Email: " << email << endl;
}