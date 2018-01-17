#include "task.h"

Task::Task(const unsigned int _id, const QString & _description, const QString &_implementer,
     const QDate & _date, bool _local):
    id(_id),
    description(_description),
    implementer(_implementer),
    date(_date),
    local(_local){}


Task::Task()
{}

QJsonObject Task::toJson() const
{
    QJsonObject object;
    object.insert("id", QJsonValue(id));
    object.insert("description", QJsonValue(description));
    object.insert("implementer", QJsonValue(implementer));
    object.insert("date", QJsonValue(date.toString("dd/MM/yyyy")));
    object.insert("local", QJsonValue(local));
    return object;
}

Task Task::fromJson(QJsonObject json)
{
    return Task(json["id"].toInt(),
                json["description"].toString(),
                json["implementer"].toString(),
                QDate::fromString(json["date"].toString(), "dd/MM/yyyy"),
                json["local"].toInt() > 0);
}
