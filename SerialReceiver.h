#ifndef SERIAL_RECEIVER_H
#define SERIAL_RECEIVER_H

#include <QtCore>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStandardItemModel>

#include "MessageHandler.h"
#include "main.h"

class SerialReceiver : public QObject
{
Q_OBJECT
public:
    explicit SerialReceiver(QObject *parent = nullptr);
    ~SerialReceiver() override {delete m_serial;}
    bool isConnected() const {return isConnect;}
    QString getConsole() const {return console;}
    QString getRawData() const {return rawData;}

public slots:

signals:
    void consoleUpdate();
    void rawDataUpdate();

private:
    QSerialPort *m_serial;
    bool isConnect = false;
    bool isIdle = true;
    QString temp;
    MessageHandler msgHandler;
    QString console;
    QString rawData;

    void readData();
};


#endif