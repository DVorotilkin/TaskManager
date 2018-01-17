#ifndef EXPORTSRTTINGS_H
#define EXPORTSRTTINGS_H

#include <QDialog>
#include "addclientdialog.h"
#include "dbmanager.h"

namespace Ui {
class ExportSrttings;
}

class ExportSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ExportSettings(DBManager *_dbManager, QWidget *parent = 0);
     void addClient(const QString &name, const QString &ip);
    ~ExportSettings();

private slots:
    void on_delClientButton_clicked();

    void on_addClientButton_clicked();

private:
    Ui::ExportSrttings *ui;
    DBManager *dbManager;
    void showClientsList(QList<Client> clients);
    void addRow(Client client, int i);

};

#endif // EXPORTSRTTINGS_H
