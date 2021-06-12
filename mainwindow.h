//
// Created by lao_jk on 2021/6/11.
//

#ifndef LOGGER_MAINWINDOW_H
#define LOGGER_MAINWINDOW_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStandardItemModel>
#include "MessageHandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial;
    bool isIdle = true;
    QString temp;
    MessageHandler msgHandler;
    QStandardItemModel* model_msg;
    QStandardItemModel* model_state;
    int num_msg=0;
    int num_state=0;
    QList<QString> stateList;

    void readData();
    bool decode();
    void editConsole(QString msg);
};


#endif //LOGGER_MAINWINDOW_H
