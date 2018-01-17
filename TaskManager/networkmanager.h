#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QJsonDocument>
#include "dbmanager.h"

class NetworkManager: public QObject
{
    Q_OBJECT
public:
    NetworkManager(const unsigned int _port, DBManager *_dbManager);
    void sendBase();
    void sendTask(const Task &task);
    void callBases();
    void setDB(DBManager *_dbManager);
private:
    QTcpServer server;
    unsigned int port;
    DBManager * dbManager;

private slots:
    void acceptConnection();
    void getBase();
    void serverReadData();
    void deleteClient();

    void errorSlot(QAbstractSocket::SocketError);
signals:
    void error(QString);

private:
    enum MessageType
{
    Base = 1,
    OneTask = 2,
    CallBase = 3
};
};

#endif // NETWORKMANAGER_H
