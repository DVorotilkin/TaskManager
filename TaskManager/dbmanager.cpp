#include "dbmanager.h"

DBManager::DBManager(QString dbFileName):
    QObject()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(dbFileName);
    state = db.open();
    QSqlQuery q(db);
    if (!state)
        emit error("Open db error: " + q.lastError().text());
    else
    {
        if (!db.tables().contains("Tasks"))
        {
            state = q.exec("CREATE TABLE `Tasks` ("
                       "`Id`	INTEGER,"
                       "`Description`	TEXT NOT NULL,"
                       "`Implementer`	TEXT NOT NULL,"
                       "`Date`	TEXT NOT NULL,"
                       "'Local' INTEGER NOT NULL,"
                       "PRIMARY KEY(`Id`));");
            if (!state)
                emit error("Create Tasks table error: " + q.lastError().text());
        }
        if (!db.tables().contains("Clients"))
        {
            state = q.exec("CREATE TABLE `Clients` ("
                           "`Id`	INTEGER,"
                           "`Name`	TEXT,"
                           "`IP`	TEXT NOT NULL UNIQUE,"
                           "PRIMARY KEY(`Id`));");
            if (!state)
                emit error("Create Clients table error: " + q.lastError().text());
        }
    }

}

DBManager::~DBManager()
{
    db.close();
}

QList<Task> &DBManager::loadTasks()
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
                  QDate::fromString(q.value("Date").toString(), "dd/MM/yyyy"),
                  q.value("Local").toInt() > 0);
        taskList.push_back(task);
    }
    if (!state)
        emit error("Load tasks error: " + q.lastError().text());
    return taskList;
}

QList<Client> &DBManager::loadClients()
{
    QSqlQuery q(db);
    q.prepare("SELECT * FROM Clients;");

    state = q.exec();
    taskList.clear();
    while (q.next())
    {
        Client client(q.value("Id").toInt(),
                      q.value("Name").toString(),
                      q.value("IP").toString());
        clientList.push_back(client);
    }
    if (!state)
        emit error("Load tasks error: " + q.lastError().text());
    return clientList;
}

int DBManager::addTask(const QString & _description, const QString &_implementer, const QDate &_date, bool _local)
{

    QSqlQuery q(db);
    q.prepare("INSERT INTO Tasks (Description, Implementer, Date, Local)"
              "VALUES (:description, :implementer, :date, :local);");

    q.bindValue(":description", _description);
    q.bindValue(":implementer", _implementer);
    q.bindValue(":date", _date.toString("dd/MM/yyyy"));
    q.bindValue((":local"), _local);
    state = q.exec();

    if (state)
        taskList.append(Task(q.lastInsertId().toInt(), _description, _implementer, _date, _local));
    else
        emit error("Add task error: " + q.lastError().text());
    return q.lastInsertId().isValid()? q.lastInsertId().toInt(): -1;
}

void DBManager::addTask(const Task &task)
{
    foreach (auto i, taskList)
        if (i.id == task.id)
            return;
    addTask(task.description, task.implementer, task.date, task.local);
}

int DBManager::addClient(const QString &name, const QString &ip)
{
    QSqlQuery q(db);
    q.prepare("INSERT INTO Clients (Name, IP)"
              "VALUES (:name, :ip);");

    q.bindValue(":name", name);
    q.bindValue(":ip", ip);
    state = q.exec();

    if (state)
        clientList.append(Client(q.lastInsertId().toInt(), name, ip));
    else
        emit error("Add client error: " + q.lastError().text());
    return q.lastInsertId().isValid()? q.lastInsertId().toInt(): -1;
}

void DBManager::deleteClient(int id)
{
    QSqlQuery q(db);
    q.prepare("DELETE INTO Clients "
              "WHERE (Id == :id);");
    q.bindValue(":id", id);
    state = q.exec();

    if (state)
    {
        auto i = clientList.begin();
        while (i->id != id && i != clientList.end())
            ++i;
        clientList.erase(i);
    }
    else
        emit error("Del client error: " + q.lastError().text());
}

QList<Task> &DBManager::getTasks()
{
    return taskList;
}

QList<Client> &DBManager::getClients()
{
    return clientList;
}

bool DBManager::getState()
{
    return state;
}
