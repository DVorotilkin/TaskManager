#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>
#include <QStringList>
#include <QList>
#include <QDebug>
#include <QVariant>
#include "task.h"

class DBManager: public QObject
{
    Q_OBJECT
public:
    DBManager(QString dbFileName);
    ~DBManager();
    QList<Task> &loadTasks();
    QList<Task> &getTasks();
    QList<Client> &loadClients();
    QList<Client> &getClients();
    int addTask(const QString & _description, const QString &_implementer,
                const QDate & _date, bool _local);
    void addTask(const Task &task);
    int addClient(const QString & name, const QString &ip);
    void deleteClient(int id);
    void editClient(const int id, const QString & name, const QString &ip);
    bool getState();

private:

    bool state;
    QSqlDatabase db;
    QList<Task> taskList;
    QList<Client> clientList;
signals:
    void error(QString message);
};

#endif // DBMANAGER_H
