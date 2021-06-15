//
// Created by lao_jk on 2021/6/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::MainWindow)
        {

    ui->setupUi(this);

    QObject::connect(&rx, &SerialReceiver::consoleUpdate, this, &MainWindow::editConsole);
    QObject::connect(&rx, &SerialReceiver::rawDataUpdate, this, &MainWindow::editRawData);

    model_msg = new QStandardItemModel();
    model_state = new QStandardItemModel();
    QStringList label_msg = QObject::trUtf8("Time,Level,Message").simplified().split(",");
    QStringList label_state = QObject::trUtf8("Time,Level,Name,Value").simplified().split(",");
    model_msg->setHorizontalHeaderLabels(label_msg);
    model_state->setHorizontalHeaderLabels(label_state);
    ui->table_msg->setModel(model_msg);
    ui->table_log->setModel(model_state);

    ui->table_msg->horizontalHeader()->resizeSection(0,90);
    ui->table_msg->horizontalHeader()->resizeSection(1,80);
    ui->table_msg->horizontalHeader()->setStretchLastSection(true);

    ui->table_log->horizontalHeader()->resizeSection(0,90);
    ui->table_log->horizontalHeader()->resizeSection(1,80);
    ui->table_log->horizontalHeader()->resizeSection(2,150);
    ui->table_log->horizontalHeader()->setStretchLastSection(true);

    if(rx.isConnected())
        ui->console->setText("Successfully Connected\n");
    else
        ui->console->setText("There are NO available ports, started the program as log reader!\n");

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::editConsole() {
    ui->console->setText(ui->console->toPlainText()+rx.getConsole()+"\n");
    ui->console->moveCursor(QTextCursor::End);
}

void MainWindow::editRawData() {
    ui->textarea->setText(ui->textarea->toPlainText()+rx.getRawData());
    ui->textarea->moveCursor(QTextCursor::End);
    decode(rx.getRawData());
}

bool MainWindow::decode(QString temp) {
    bool isState; int msgLevel;
    if(temp[0] != '&') return false;

    if(temp[1]=='S') isState = true;
    else if(temp[1]=='M') isState = false;
    else return false;

    msgLevel = temp[2].digitValue();
    if(msgLevel < 1 || msgLevel > 4) return false;
    QString level;
    switch (msgLevel) {
        case 1:
            level="ERROR";
            break;
        case 2:
            level="Warning";
            break;
        case 3:
            level="Note";
            break;
        case 4:
            level="Info";
            break;
        default:
            level="N/A";
            break;
    }

    if(temp[3] != HEADER_CHAR || temp[temp.length()-1] != END_CHAR) return false;

    if (isState) {
        foreach(QString str, temp.mid(4,temp.length()-5).split(SEPARATE_CHAR)) {
            QString name = str.split(STATE_CHAR)[0];
            QString value = str.split(STATE_CHAR)[1];
            if(stateList.contains(name)) {
                int rowNum = stateList.indexOf(name);
                model_state->setItem(rowNum, 0,
                                     new QStandardItem(QDateTime::currentDateTime().toString("hh:mm:ss")));
                model_state->setItem(rowNum,1,new QStandardItem(level));
                model_state->setItem(rowNum, 3, new QStandardItem(value));
            }
            else {
                stateList.append(name);
                model_state->setItem(num_state, 0,
                                     new QStandardItem(QDateTime::currentDateTime().toString("hh:mm:ss")));
                model_state->setItem(num_state,1,new QStandardItem(level));
                model_state->setItem(num_state, 2, new QStandardItem(name));
                model_state->setItem(num_state, 3, new QStandardItem(value));
                num_state++;
            }
        }
        ui->table_log->scrollToBottom();
    }
    else {
        model_msg->setItem(num_msg,0,
                       new QStandardItem(QDateTime::currentDateTime().toString("hh:mm:ss")));
        model_msg->setItem(num_msg,1,new QStandardItem(level));
        model_msg->setItem(num_msg,2,
                       new QStandardItem(temp.mid(4, temp.length()-5)));
        num_msg++;
        ui->table_msg->scrollToBottom();
    }

    return true;
}


