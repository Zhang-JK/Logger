#include <QApplication>
#include <QDebug>

#include "main.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

#ifdef USE_GUI
    MainWindow w;
    w.setWindowTitle("RM2021 Logger");
    w.show();
#else
    SerialReceiver rx;
#endif

#ifdef USE_GUI
    return QApplication::exec();
#else
    if(rx.isConnected()) {
        return QApplication::exec();
        qDebug() << "Started in non-desktop mode";
    }
    else
        qDebug() << "There are NO available ports, program exit :(";
#endif

}
