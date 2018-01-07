#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>
#include <QStringList>
#include <QList>
#include <QDebug>
#include <QVariant>
#include "task.h"

class DBManager
{
public:
    DBManager();
    ~DBManager();
    QList<Task> & loadDB();
    QList<Task> &getTasks();
    int addTask(const QString & _decription, const QString &_implementer,
                const QDate & _date);
    bool getState();
private:
    bool state;
    QSqlDatabase db;
    QList<Task> taskList;
};

#endif // DBMANAGER_H
