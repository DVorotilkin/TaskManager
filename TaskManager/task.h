#ifndef TASK_H
#define TASK_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QDate>

struct Client
{
    Client() {}
    Client(const unsigned int _id, const QString &_name, const QString &_ip):
        id(_id),
        name(_name),
        IP(_ip){}
    int id;
    QString name, IP;
};


class Task
{
public:
    Task(const unsigned int _id, const QString & _description, const QString & _implementer,
         const QDate & _date, bool _local);
    Task();
    QJsonObject toJson() const;
    static Task fromJson(QJsonObject json);
    int id;
    QString description, implementer;
    QDate date;
    bool local;
};


#endif // TASK_H
