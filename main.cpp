#include <QApplication>
#include "gui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Style toàn ứng dụng
    app.setStyleSheet(R"(
        * {
            font-family: "Segoe UI", "Arial", sans-serif;
            font-size: 14px;
        }

        QWidget {
            background-color: #f5f7fb;
            color: #1f2937;
        }

        QMainWindow {
            background-color: #f5f7fb;
        }

        QTabWidget::pane {
            border: 1px solid #dbe3ef;
            background: #ffffff;
            border-radius: 14px;
            top: -1px;
        }

        QTabBar::tab {
            background: #e9eef7;
            color: #475569;
            padding: 10px 18px;
            margin-right: 6px;
            border-top-left-radius: 10px;
            border-top-right-radius: 10px;
            min-width: 140px;
            font-weight: 600;
        }

        QTabBar::tab:selected {
            background: #ffffff;
            color: #2563eb;
        }

        QTabBar::tab:hover:!selected {
            background: #dfe7f5;
        }

        QGroupBox {
            background: #ffffff;
            border: 1px solid #e5e7eb;
            border-radius: 14px;
            margin-top: 14px;
            padding: 18px 14px 14px 14px;
            font-weight: 700;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            left: 14px;
            padding: 0 8px;
            color: #111827;
        }

        QLabel {
            background: transparent;
        }

        QLineEdit, QDateEdit, QComboBox, QSpinBox {
            background: #ffffff;
            border: 1px solid #d1d9e6;
            border-radius: 10px;
            padding: 8px 10px;
            min-height: 18px;
        }

        QLineEdit:focus, QDateEdit:focus, QComboBox:focus, QSpinBox:focus {
            border: 1px solid #3b82f6;
        }

        QPushButton {
            background-color: #ffffff;
            border: 1px solid #d1d5db;
            border-radius: 10px;
            padding: 8px 14px;
            min-height: 34px;
            font-weight: 600;
        }

        QPushButton:hover {
            background-color: #f3f6fb;
        }

        QPushButton:pressed {
            background-color: #e5ecf6;
        }

        QTableWidget {
            background: #ffffff;
            border: 1px solid #e5e7eb;
            border-radius: 12px;
            gridline-color: #eef2f7;
            selection-background-color: #dbeafe;
            selection-color: #1e3a8a;
            alternate-background-color: #f9fbfe;
        }

        QHeaderView::section {
            background-color: #eef4fb;
            color: #334155;
            padding: 10px;
            border: none;
            border-bottom: 1px solid #dbe3ef;
            font-weight: 700;
        }

        QTableCornerButton::section {
            background-color: #eef4fb;
            border: none;
            border-bottom: 1px solid #dbe3ef;
        }

        QScrollBar:vertical {
            background: transparent;
            width: 10px;
            margin: 4px;
        }

        QScrollBar::handle:vertical {
            background: #cbd5e1;
            min-height: 30px;
            border-radius: 5px;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0px;
        }

        QScrollBar:horizontal {
            background: transparent;
            height: 10px;
            margin: 4px;
        }

        QScrollBar::handle:horizontal {
            background: #cbd5e1;
            min-width: 30px;
            border-radius: 5px;
        }

        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            width: 0px;
        }

        QMessageBox {
            background-color: #ffffff;
        }
    )");

    MainWindow window;
    window.show();

    return app.exec();
}