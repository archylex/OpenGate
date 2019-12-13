#include "askpassdialog.h"
#include "ui_askpassdialog.h"

askPassDialog::askPassDialog(QString &value, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askPassDialog) {
    pValue = &value;
    ui->setupUi(this);
}

askPassDialog::~askPassDialog() {
    delete ui;
}

void askPassDialog::on_pushButton_clicked() {    
    *pValue = ui->lineEdit->text();
    ui->lineEdit->setText("");
    this->close();
}
