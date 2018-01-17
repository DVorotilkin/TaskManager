#include "addclientdialog.h"
#include "ui_addclientdialog.h"

AddClientDialog::AddClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClientDialog)
{
    ui->setupUi(this);
}

AddClientDialog::~AddClientDialog()
{
    delete ui;
}

void AddClientDialog::on_cancelButton_clicked()
{
    this->destroy();
}

void AddClientDialog::on_okButton_clicked()
{
    ((ExportSettings*)parent())->addClient(ui->lineEdit->text(),
                                       ui->lineEdit_2->text());
    this->destroy();
}
