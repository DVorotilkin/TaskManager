#include "addtaskdialog.h"
#include "ui_addtaskdialog.h"

AddTaskDialog::AddTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskDialog)
{
    ui->setupUi(this);
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

void AddTaskDialog::on_cancelButton_clicked()
{
    this->destroy();
}

void AddTaskDialog::on_okButton_clicked()
{
    ((MainWindow*)parent())->addTask(ui->textEdit->toPlainText(),
                                     ui->lineEdit->text(),
                                     ui->dateEdit->date(),
                                     ui->checkBox->isChecked());
    this->destroy();
}
