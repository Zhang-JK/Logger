#include <QApplication>
#include <QDebug>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle("RM2021 Logger");
    w.show();

    return QApplication::exec();
}
