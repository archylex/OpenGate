#include "threadcommand.h"

ThreadCommand::ThreadCommand() {    
}

void ThreadCommand::run() {
    int a = system(cmd);
    *code = a;
}

void ThreadCommand::setCommand(QString cm, int &cd) {
    QByteArray b = cm.toLocal8Bit();
    cmd = b.data();qDebug() << cmd;
    code = &cd;
}
