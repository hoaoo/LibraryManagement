cmake_minimum_required(VERSION 4.1)
project(LibraryManagement)

set(CMAKE_CXX_STANDARD 20)

add_executable(LibraryManagement main.cpp
        models/Book.h
        models/Book.cpp
        models/Reader.h
        models/Reader.cpp
        models/BorrowRecord.h
        models/BorrowRecord.cpp
        services/LibraryManager.h
        services/LibraryManager.cpp
        utils/FileHandler.h
        utils/FileHandler.cpp
        utils/Validator.h
        utils/Validator.cpp)
