#include <QApplication>
#include <QPushButton>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    window.setWindowTitle("Maze Generator Visualizer");
    window.resize(500, 800);
    window.show();
    return QApplication::exec();
}
