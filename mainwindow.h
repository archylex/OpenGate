#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QFile>
#include <QTextStream>
#include <askpassdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    QNetworkAccessManager manager;
    QStringList confData;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void insertToTbale();
    ~MainWindow();

public slots:
    void insertToTable(QString country, QString ip, QString ping, QString speed, QString uptime, QString users, QString opername);
    void replyFinished(QNetworkReply *reply);

private slots:
    void on_refreshButton_clicked();
    void on_connectButton_clicked();
    void runCommand();
    void runErrDlg();
    void on_disconnectButton_clicked();

private:
    Ui::MainWindow *ui;
    QString pass;
    QString bCmd;
    int code;
};

#endif // MAINWINDOW_H
