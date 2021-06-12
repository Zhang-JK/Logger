#include "MessageHandler.h"

QString MessageHandler::saveMsg(QString msg) {
//    qDebug() << msg;
    if(!isInit) init();
    if(isInit && logFile->open(QIODevice::Append)) {
        logFile->write(QDateTime::currentDateTime().toString("MM.dd-hh:mm:ss").toLocal8Bit());
        logFile->write(" ");
        logFile->write(msg.toLocal8Bit());
        logFile->close();
        return "";
    }
    else
        return "FAIL TO LOAD THE FILE";
}

bool MessageHandler::init() {
    if(isInit) return true;

    QDir fileDir(logDir);
    if(!fileDir.exists()) {
        fileDir.mkpath(".test");
    }

    logFile = new QFile(logDir+QDateTime::currentDateTime().toString("MM.dd-hh:mm:ss")+".log");

    if(logFile->open(QIODevice::WriteOnly)) {
        isInit=true;
        logFile->write("Enterprise Robot Working Log\n");
        logFile->write("Version 1.0 ZHANG Jiekai\n");
        logFile->write("Format: \"Time\" \"Message\" \n");
        logFile->write("------------------------------------------------\n");
        logFile->close();
    }

    return isInit;
}

