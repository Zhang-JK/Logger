#include <QDebug>
#include "main.h"

#ifdef USE_GUI
#include <QApplication>
#include "mainwindow.h"
#else
#include <QCoreApplication>
#include "SerialReceiver.h"
#endif

int main(int argc, char *argv[]) {
#ifdef USE_GUI
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle("RM2021 Logger");
    w.show();
    return QApplication::exec();
#else
    QCoreApplication app(argc, argv);
    SerialReceiver rx;
    if(rx.isConnected()) {
        qDebug() << "Started in non-desktop mode";
        return app.exec();
    }
    else
        qDebug() << "There are NO available ports, program exit :(";
#endif

#ifdef USE_GUI

#else

#endif

}
