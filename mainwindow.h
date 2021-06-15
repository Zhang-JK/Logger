#ifndef LOGGER_MAINWINDOW_H
#define LOGGER_MAINWINDOW_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStandardItemModel>
#include "SerialReceiver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:
    void editConsole();
    void editRawData();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model_msg;
    QStandardItemModel* model_state;
    int num_msg=0;
    int num_state=0;
    QList<QString> stateList;
    SerialReceiver rx;

    bool decode(QString);
};


#endif //LOGGER_MAINWINDOW_H
