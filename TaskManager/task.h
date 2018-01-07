#ifndef TASK_H
#define TASK_H

#include <QJsonDocument>
#include <QDate>

class Task
{
public:
    Task(const unsigned int _id, const QString & _decription, const QString & _implementer,
         const QDate & _date);
    Task();
    unsigned int id;
    QString decription, implementer;
    QDate date;
};


#endif // TASK_H
