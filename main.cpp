#include <QApplication>
#include "gui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setStyleSheet(R"(
        QWidget {
            font-size: 14px;
        }
        QMainWindow {
            background-color: #f5f6fa;
        }
        QTabWidget::pane {
            border: 1px solid #dcdde1;
            background: white;
            border-radius: 8px;
        }
        QTabBar::tab {
            background: #dfe6e9;
            padding: 10px 16px;
            margin-right: 4px;
            border-top-left-radius: 6px;
            border-top-right-radius: 6px;
        }
        QTabBar::tab:selected {
            background: #ffffff;
            font-weight: bold;
        }
        QPushButton {
            min-height: 32px;
            padding: 6px 14px;
            border: 1px solid #b2bec3;
            border-radius: 6px;
            background-color: #ffffff;
        }
        QPushButton:hover {
            background-color: #ecf0f1;
        }
        QLineEdit, QDateEdit, QTableWidget {
            border: 1px solid #dcdde1;
            border-radius: 6px;
            padding: 4px;
            background: white;
        }
        QGroupBox {
            font-weight: bold;
            border: 1px solid #dcdde1;
            border-radius: 8px;
            margin-top: 12px;
            padding-top: 12px;
            background: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 6px 0 6px;
        }
    )");

    MainWindow window;
    window.show();

    return app.exec();
}