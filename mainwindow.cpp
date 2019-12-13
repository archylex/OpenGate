#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadcommand.h"
#include "errordialog.h"

QString URL = "http://www.vpngate.net/api/iphone/";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
    manager.get(QNetworkRequest(QUrl(URL)));

    QStringList titles;
    titles << "Country" << "IP" << "Ping" << "Speed" << "Uptime" << "Total Users" << "Operator";
    ui->tableWidget->setEnabled(false);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(titles);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(16);
    QHeaderView *horizontalHeader = ui->tableWidget->horizontalHeader();
    horizontalHeader->setSectionResizeMode(3, QHeaderView::Fixed);
    horizontalHeader->setSectionResizeMode(4, QHeaderView::Fixed);
    horizontalHeader->setSectionResizeMode(5, QHeaderView::Fixed);
    horizontalHeader->setSectionResizeMode(6, QHeaderView::Fixed);
    horizontalHeader->setDefaultSectionSize(80);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::insertToTable(QString country, QString ip, QString ping, QString speed, QString uptime, QString users, QString opername) {
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int posCell = ui->tableWidget->rowCount() - 1;
    ui->tableWidget->setItem(posCell, 0, new QTableWidgetItem(country));
    ui->tableWidget->setItem(posCell, 1, new QTableWidgetItem(ip));
    ui->tableWidget->setItem(posCell, 2, new QTableWidgetItem(ping));
    ui->tableWidget->setItem(posCell, 3, new QTableWidgetItem(speed));
    ui->tableWidget->setItem(posCell, 4, new QTableWidgetItem(uptime));
    ui->tableWidget->setItem(posCell, 5, new QTableWidgetItem(users));
    ui->tableWidget->setItem(posCell, 6, new QTableWidgetItem(opername));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply) {
    ui->label->setVisible(false);
    ui->tableWidget->setEnabled(true);
    
	bool firstLine = true;

    while (!reply->atEnd()) {
        QByteArray bytes = reply->readLine();
        QString str = QString::fromUtf8(bytes.data(), bytes.size());
        QStringList arr = str.split(",");
    
		if(arr.length() > 14) {
            if(!firstLine) {
                confData.append(arr.value(14));
                int speed = arr.value(4).toInt() / (1024 * 1024);
                insertToTable(arr.value(5),arr.value(1),arr.value(3),QString::number(speed) + " Mb/s", arr.value(8), arr.value(9), arr.value(12));
            }
        
			firstLine = false;
        }
    }
}

void MainWindow::runErrDlg() {
    ErrorDialog *errDlg = new ErrorDialog(code, this);
    errDlg->setAttribute(Qt::WA_DeleteOnClose);
    errDlg->exec();

    ui->connectButton->setDisabled(false);
    ui->disconnectButton->setDisabled(true);
}

void MainWindow::runCommand() {
    ThreadCommand *tComm = new ThreadCommand;
    QString command = "echo '" + pass + "' | sudo -S " + bCmd;
    
	tComm->setCommand(command, code);
    
	connect(tComm, SIGNAL(finished()), SLOT(runErrDlg()));
    
	tComm->start();
}

void MainWindow::on_refreshButton_clicked() {
    ui->tableWidget->model()->removeRows(0, ui->tableWidget->rowCount());
    ui->label->setVisible(true);
    ui->tableWidget->setEnabled(false);

    manager.get(QNetworkRequest(QUrl(URL)));
}

void MainWindow::on_connectButton_clicked() {
    QList<QTableWidgetItem*> selectionRangeList = ui->tableWidget->selectedItems();
    int rowIndex;
    QListIterator<QTableWidgetItem*> selectionRangeListIter(selectionRangeList);
    QFile file("/tmp/conf.ovpn");

    while(selectionRangeListIter.hasNext()) {
        rowIndex = ((int)((QTableWidgetItem*)selectionRangeListIter.next())->row());
    }

    QByteArray b = confData.value(rowIndex).toLocal8Bit();
    QString ff = QByteArray::fromBase64(b);

    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << ff << endl;
    }

    bCmd = "openvpn /tmp/conf.ovpn";

    askPassDialog *askDlg = new askPassDialog(pass, this);
    askDlg->setAttribute(Qt::WA_DeleteOnClose);
    connect(askDlg, SIGNAL(destroyed(QObject*)), SLOT(runCommand()));
    askDlg->exec();

    ui->connectButton->setDisabled(true);
    ui->disconnectButton->setDisabled(false);
}

void MainWindow::on_disconnectButton_clicked() {
    bCmd = "killall openvpn";

    askPassDialog *askDlg = new askPassDialog(pass, this);    
	askDlg->setAttribute(Qt::WA_DeleteOnClose);
    connect(askDlg, SIGNAL(destroyed(QObject*)), SLOT(runCommand()));
    askDlg->exec();

    ui->connectButton->setDisabled(false);
    ui->disconnectButton->setDisabled(true);
}
