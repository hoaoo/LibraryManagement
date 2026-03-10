#include "Book.h"
#include <iostream>
#include <iomanip>

using namespace std;

Book::Book() : quantity(0), available(0) {}

Book::Book(string bookId, string title, string author, string category, int quantity, int available)
        : bookId(bookId), title(title), author(author), category(category), quantity(quantity), available(available) {}

string Book::getBookId() const {
    return bookId;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getCategory() const {
    return category;
}

int Book::getQuantity() const {
    return quantity;
}

int Book::getAvailable() const {
    return available;
}

void Book::setBookId(const string& bookId) {
    this->bookId = bookId;
}

void Book::setTitle(const string& title) {
    this->title = title;
}

void Book::setAuthor(const string& author) {
    this->author = author;
}

void Book::setCategory(const string& category) {
    this->category = category;
}

void Book::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Book::setAvailable(int available) {
    this->available = available;
}

void Book::display() const {
    cout << left
         << setw(10) << bookId
         << setw(30) << title
         << setw(25) << author
         << setw(20) << category
         << setw(10) << quantity
         << setw(10) << available
         << endl;
}