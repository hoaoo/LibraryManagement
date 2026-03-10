cmake_minimum_required(VERSION 3.16)
project(LibraryManagement)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(LibraryManagement
        main.cpp

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
        utils/Validator.cpp

        gui/MainWindow.h
        gui/MainWindow.cpp
        gui/BookTab.h
        gui/BookTab.cpp
        gui/ReaderTab.h
        gui/ReaderTab.cpp
        gui/BorrowTab.h
        gui/BorrowTab.cpp
        gui/StatisticsTab.h
        gui/StatisticsTab.cpp
)

target_link_libraries(LibraryManagement PRIVATE Qt6::Widgets)