#include "errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(int code, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog) {
    ui->setupUi(this);
	    
	switch (code)
	{
		case 256:
			ui->label->setText("Incorrect root password");
			break;
		case 0:
			ui->label->setText("The connection was interrupted");
			break;
		default:
			break;
	}        
}

ErrorDialog::~ErrorDialog() {
    delete ui;
}

void ErrorDialog::on_pushButton_clicked() {
    close();
}
