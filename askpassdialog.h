#ifndef ASKPASSDIALOG_H
#define ASKPASSDIALOG_H

#include <QDialog>

namespace Ui {
class askPassDialog;
}

class askPassDialog : public QDialog {
    Q_OBJECT

public:
    explicit askPassDialog(QString &value, QWidget *parent = nullptr);
    ~askPassDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::askPassDialog *ui;
    QString *pValue;
};

#endif // ASKPASSDIALOG_H
