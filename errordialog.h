#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog {
    Q_OBJECT

public:
    explicit ErrorDialog(int code, QWidget *parent = nullptr);
    ~ErrorDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
