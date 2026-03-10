#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
private:
    string bookId;
    string title;
    string author;
    string category;
    int quantity;
    int available;

public:
    Book();
    Book(string bookId, string title, string author, string category, int quantity, int available);

    string getBookId() const;
    string getTitle() const;
    string getAuthor() const;
    string getCategory() const;
    int getQuantity() const;
    int getAvailable() const;

    void setBookId(const string& bookId);
    void setTitle(const string& title);
    void setAuthor(const string& author);
    void setCategory(const string& category);
    void setQuantity(int quantity);
    void setAvailable(int available);

    void display() const;
};

#endif