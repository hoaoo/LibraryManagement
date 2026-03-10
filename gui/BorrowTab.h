#ifndef BORROWTAB_H
#define BORROWTAB_H

#include <QWidget>
#include "../services/LibraryManager.h"

class QLineEdit;
class QPushButton;
class QTableWidget;
class QDateEdit;

// Tab quản lý mượn / trả sách
class BorrowTab : public QWidget {
    Q_OBJECT

public:
    explicit BorrowTab(LibraryManager& manager, QWidget *parent = nullptr);

private slots:
    // Xử lý mượn sách
    void onBorrowBook();

    // Xử lý trả sách
    void onReturnBook();

    // Tải lại lịch sử mượn / trả
    void onRefreshHistory();

private:
    // Tham chiếu đến bộ quản lý dữ liệu dùng chung
    LibraryManager& manager;

    // Form mượn sách
    QLineEdit *readerIdEdit;
    QLineEdit *bookIdEdit;
    QDateEdit *borrowDateEdit;
    QPushButton *borrowButton;

    // Form trả sách
    QLineEdit *returnReaderIdEdit;
    QLineEdit *returnBookIdEdit;
    QDateEdit *returnDateEdit;
    QPushButton *returnButton;

    // Bảng lịch sử và nút refresh
    QPushButton *refreshButton;
    QTableWidget *historyTable;

    // Khởi tạo giao diện
    void setupUi();

    // Đổ dữ liệu lịch sử lên bảng
    void loadHistory();
};

#endif