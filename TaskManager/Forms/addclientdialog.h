#ifndef ADDCLIENTDIALOG_H
#define ADDCLIENTDIALOG_H

#include <QDialog>
#include "exportsettings.h"

namespace Ui {
class AddClientDialog;
}

class AddClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClientDialog(QWidget *parent = 0);
    ~AddClientDialog();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::AddClientDialog *ui;
};

#endif // ADDCLIENTDIALOG_H
