#include "dbmanager.h"

DBManager::DBManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("Tasks.db");
    state = db.open();
    QSqlQuery q(db);
    state = q.exec("PRAGMA foreign_keys = ON;");
    if (!state)
        qDebug() << "Open db error: " << q.lastError().text();
    else if (!db.tables().contains("Tasks"))
    {
        state = q.exec("CREATE TABLE `Tasks` ("
                   "`Id`	INTEGER,"
                   "`Description`	TEXT NOT NULL,"
                   "`Implementer`	TEXT NOT NULL,"
                   "`Date`	TEXT NOT NULL,"
                   "PRIMARY KEY(`Id`));");
        if (!state)
            qDebug() << "Create table error: " << q.lastError().text();
    }

}

DBManager::~DBManager()
{
    db.close();
}

QList<Task> &DBManager::loadDB()
{
    QSqlQuery q(db);
    q.prepare("SELECT * FROM Tasks;");

    state = q.exec();
    taskList.clear();
    while (q.next())
    {
        Task task(q.value("Id").toInt(),
                  q.value("Description").toString(),
                  q.value("Implementer").toString(),
                  QDate::fromString(q.value("Date").toString(), "dd/MM/yyy"));
        taskList.push_back(task);
    }
    if (!state)
        qDebug() << "Load tasks error: " << q.lastError().text();
    return taskList;
}

QList<Task> &DBManager::getTasks()
{
    return taskList;
}

int DBManager::addTask(const QString & _decription, const QString &_implementer, const QDate &_date)
{
    QSqlQuery q(db);
    q.prepare("INSERT INTO Tasks (Description, Implementer, Date)\n"
              "VALUES (:description, :implementer, :date);");

    q.bindValue(":description", _decription);
    q.bindValue(":implementer", _implementer);
    q.bindValue(":date", _date.toString("dd/MM/yyyy"));
    state = q.exec();

    if (state)
        taskList.append(Task(q.lastInsertId().toInt(), _decription, _implementer, _date));
    else
        qDebug() << "Add task error: " << q.lastError().text();
    return q.lastInsertId().isValid()? q.lastInsertId().toInt(): -1;
}

bool DBManager::getState()
{
    return state;
}
