#ifndef EXPORTSETTINGS_H
#define EXPORTSETTINGS_H

#include <QDialog>
#include "addclientdialog.h"
#include "dbmanager.h"
#include "networkmanager.h"
#include "mainwindow.h"

namespace Ui {
class ExportSrttings;
}

class ExportSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ExportSettings(DBManager *_dbManager, NetworkManager *_networkManager, QWidget *parent = 0);
     void addClient(const QString &name, const QString &ip);
    ~ExportSettings();

private slots:
    void on_delClientButton_clicked();

    void on_addClientButton_clicked();

    void on_portEdit_editingFinished();

private:
    Ui::ExportSrttings *ui;
    DBManager *dbManager;
    NetworkManager *networkManager;
    void showClientsList(QList<Client> clients);
    void addRow(Client client, int i);

};

#endif // EXPORTSETTINGS_H
