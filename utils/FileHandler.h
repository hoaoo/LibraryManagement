#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include "../models/Book.h"

using namespace std;

class FileHandler {
public:
    static vector<Book> loadBooksFromFile(const string& filename);
    static void saveBooksToFile(const string& filename, const vector<Book>& books);
};

#endif