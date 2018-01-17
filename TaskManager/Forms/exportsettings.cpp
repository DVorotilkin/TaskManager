#include "exportsettings.h"
#include "ui_exportsrttings.h"

ExportSettings::ExportSettings(DBManager *_dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportSrttings),
    dbManager(_dbManager)
{
    ui->setupUi(this);
    showClientsList(dbManager->getClients());
}

ExportSettings::~ExportSettings()
{
    delete ui;
}

void ExportSettings::addRow(Client client, int i)
{
    QTableWidgetItem *nameItem = new QTableWidgetItem(client.name);
    QTableWidgetItem *ipItem = new QTableWidgetItem(client.IP);
    ui->tableWidget->setItem(i, 0, nameItem);
    ui->tableWidget->setItem(i, 1, ipItem);
}

void ExportSettings::showClientsList(QList<Client> clients)
{
    auto it = clients.begin();
    ui->tableWidget->setRowCount(clients.length());
    for (int i = 0; i < clients.length(); ++i)
    {
        addRow(*it, i);
        ++it;
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void ExportSettings::on_delClientButton_clicked()
{
    dbManager->deleteClient(
        dbManager->getClients().at(
        ui->tableWidget->currentRow()).id);
}

void ExportSettings::addClient(const QString &name, const QString &ip)
{
    dbManager->addClient(name, ip);
}

void ExportSettings::on_addClientButton_clicked()
{
    AddClientDialog *addClientDlg = new AddClientDialog(this);
    addClientDlg->show();
}
