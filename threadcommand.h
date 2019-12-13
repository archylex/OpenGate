#ifndef THREADCOMMAND_H
#define THREADCOMMAND_H

#include <QtCore>

class ThreadCommand : public QThread {
public:
    ThreadCommand();
    void run();
    void setCommand(QString cm, int &cd);

private:
    const char *cmd;
    int *code;
};

#endif // THREADCOMMAND_H
