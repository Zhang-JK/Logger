//
// Created by lao_jk on 2021/6/11.
//

#ifndef LOGGER_MESSAGEHANDLER_H
#define LOGGER_MESSAGEHANDLER_H

#include <QtCore>

#define START_CHAR '&'
#define END_CHAR '\n'
#define HEADER_CHAR '-'
#define SEPARATE_CHAR ';'
#define STATE_CHAR ':'

/*
 * Message Example:
 * &0.0:<MSG>.<STATE>:<MSG>.<STATE>!
 */

class MessageHandler {
   public:
    MessageHandler() : isInit(false), logDir("./log/"), logFile(nullptr) {}
    ~MessageHandler() {
//        logFile->close();
        delete logFile;
    }
    QString saveMsg(QString msg);

   private:
    bool isInit;
    bool init();
    QString currentMsg;
    QString logDir;
    QFile* logFile;
};

#endif //LOGGER_MESSAGEHANDLER_H
