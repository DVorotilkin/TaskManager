#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = 0);
    ~AddTaskDialog();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::AddTaskDialog *ui;
};

#endif // ADDTASKDIALOG_H
