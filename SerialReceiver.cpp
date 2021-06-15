#include "SerialReceiver.h"

SerialReceiver::SerialReceiver(QObject *parent) :
        QObject(parent),
        m_serial(new QSerialPort(this)){

    isConnect = false;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();

        (*m_serial).setPort(info);
        m_serial->setBaudRate(QSerialPort::Baud115200);
        if ((*m_serial).open(QIODevice::ReadWrite)) {
            isConnect = true;
            qDebug() << "Successfully Connected to " << m_serial->portName();
            break;
        }
        else
            qDebug() << "Connection Failed for " << m_serial->portName();
    }
    if(isConnect) {
        connect(m_serial, &QSerialPort::readyRead, this, &SerialReceiver::readData);
        console="Successfully Connected to " + m_serial->portName();
        emit consoleUpdate();
    }
    else {
        console="There are NO available ports, started the program as log reader!";
        emit consoleUpdate();
    }
}

void SerialReceiver::readData() {
    QByteArray tempData;
    tempData = (*m_serial).read(64);

    foreach (const QChar &c, tempData) {
        if(isIdle) {
            if(c==START_CHAR) {
                temp.append(c);
                isIdle = false;
            }
        }
        else {
            if(c==START_CHAR) temp.clear();
            if(c!=END_CHAR) temp.append(c);
            else {
                temp.append(c);
                isIdle = true;
                QString ret = msgHandler.saveMsg(temp);
#ifdef USE_GUI
                if (!ret.isEmpty()){
                    console.clear();
                    console=ret;
                    emit consoleUpdate();
                }
                rawData.clear();
                rawData=temp;
                emit rawDataUpdate();
#else
                qDebug() << temp;
#endif
                temp.clear();
            }
        }
    }
}
