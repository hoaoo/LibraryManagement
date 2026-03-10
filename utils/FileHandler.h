#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include "../models/Book.h"
#include "../models/Reader.h"

using namespace std;

class FileHandler {
public:
    static vector<Book> loadBooksFromFile(const string& filename);
    static void saveBooksToFile(const string& filename, const vector<Book>& books);

    static vector<Reader> loadReadersFromFile(const string& filename);
    static void saveReadersToFile(const string& filename, const vector<Reader>& readers);
};

#endif