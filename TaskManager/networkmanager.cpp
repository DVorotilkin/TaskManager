#include "networkmanager.h"

NetworkManager::NetworkManager(const unsigned int _port, DBManager *_dbManager):
    QObject(),
    port(_port),
    dbManager(_dbManager)
{
    while (!server.isListening() && !server.listen()) {
            QMessageBox::StandardButton ret = QMessageBox::critical(nullptr,
                                            "Network error",
                                            "Unable to start the server: " +
                                            server.errorString(),
                                            QMessageBox::Retry|
                                            QMessageBox::Cancel);
            if (ret == QMessageBox::Cancel)
                return;
        }
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void NetworkManager::sendBase()
{
    auto clients = dbManager->getClients();
    for (auto i = clients.begin(); i != clients.end(); ++i)
    {
        QTcpSocket * client = new QTcpSocket();
        connect(client, &QTcpSocket::connected, [=]()
        {
            QJsonArray array;
            auto tasks = dbManager->getTasks();
            for (auto t = tasks.begin(); t != tasks.end(); ++t)
                if (!t->local)
                    array.append(QJsonValue(t->toJson()));
            QJsonObject obj;
            obj.insert("type", Base);
            obj["data"] = array;
            QJsonDocument json;
            json.setObject(obj);
            client->write(json.toBinaryData());
        });
        connect(client, &QTcpSocket::disconnected, this, &NetworkManager::deleteClient);
        client->connectToHost(QHostAddress(i->IP), port);
    }
}

void NetworkManager::getBase()
{
    auto client = (QTcpSocket*)sender();
    QJsonParseError * err = nullptr;
    auto json = QJsonDocument::fromJson(client->readAll(), err);
    if (json.isNull())
    {
        error("Cann't parse input json. Details: " + err->errorString());
        return;
    }
    auto array = json.array();
    for (auto i = array.begin(); i != array.end(); ++i)
        dbManager->addTask(Task::fromJson((*i).toObject()));
    client->disconnectFromHost();
    client->deleteLater();
}

void NetworkManager::sendTask(const Task &task)
{
    auto clients = dbManager->getClients();
    for (auto i = clients.begin(); i != clients.end(); ++i)
    {
        QTcpSocket * client = new QTcpSocket();
        connect(client, &QTcpSocket::connected, [=]()
        {
            QJsonObject obj;
            obj.insert("type", (int)OneTask);
            obj.insert("data", task.toJson());
            QJsonDocument json;
            json.setObject(obj);
            client->write(json.toBinaryData());
        });
        client->connectToHost(QHostAddress(i->IP), port);
        connect(client, &QTcpSocket::disconnected, this, &NetworkManager::deleteClient);

    }
}

void NetworkManager::callBases()
{
    auto clients = dbManager->getClients();
    for (auto i = clients.begin(); i != clients.end(); ++i)
    {
        QTcpSocket * client = new QTcpSocket();
        connect(client, &QTcpSocket::connected, [=]()
        {
            QJsonObject obj;
            obj.insert("type", CallBase);
            QJsonDocument json;
            json.setObject(obj);
            client->write(json.toBinaryData());
        });
        client->connectToHost(QHostAddress(i->IP), port);
        connect(client, &QTcpSocket::readyRead, this, &NetworkManager::getBase);
    }
}

void NetworkManager::acceptConnection()
{
    QTcpSocket *tcpServerConnection = server.nextPendingConnection();
    connect(tcpServerConnection, SIGNAL(readyRead()),
            this, SLOT(serverReadData()));
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(errorSlot(QAbstractSocket::SocketError)));
}

void NetworkManager::serverReadData()
{
    QTcpSocket *serverConnection = (QTcpSocket*)sender();
    QJsonParseError * err = nullptr;
    auto json = QJsonDocument::fromJson(serverConnection->readAll(), err);
    if (json.isNull())
    {
        error("Cann't parse input json. Details: " + err->errorString());
        delete err;
        return;
    }
    QJsonObject obj = json.object();
    MessageType type = (MessageType)obj["type"].toInt();
    switch (type) {
    case CallBase:
    {
        QJsonArray array;
        auto tasks = dbManager->getTasks();
        for (auto t = tasks.begin(); t != tasks.end(); ++t)
            if (!t->local)
                array.append(QJsonValue(t->toJson()));
        QJsonDocument json;
        json.setArray(array);
        serverConnection->write(json.toBinaryData());
        connect(serverConnection, &QTcpSocket::disconnected, this, &NetworkManager::deleteClient);
    }
        break;
    case OneTask:
    {
        dbManager->addTask(Task::fromJson(obj["data"].toObject()));
        serverConnection->disconnectFromHost();
        serverConnection->deleteLater();
    }
        break;
    case Base:
    {
        auto array = obj["data"].toArray();
        for (auto i = array.begin(); i != array.end(); ++i)
            dbManager->addTask(Task::fromJson((*i).toObject()));
        serverConnection->disconnectFromHost();
        serverConnection->deleteLater();
    }
        break;
    default:
        break;
    }
}

void NetworkManager::deleteClient()
{
    ((QTcpSocket*)sender())->deleteLater();
}

void NetworkManager::errorSlot(QAbstractSocket::SocketError)
{
    emit error("Network error: " + ((QTcpSocket*)sender())->errorString());
}

void NetworkManager::setDB(DBManager *_dbManager)
{
    dbManager = _dbManager;
}
