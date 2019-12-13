#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyle("fusion");

    MainWindow w;
    w.setWindowTitle("OpenGate");
    w.setFixedSize(w.width(), w.height());
    w.show();

    return a.exec();
}
