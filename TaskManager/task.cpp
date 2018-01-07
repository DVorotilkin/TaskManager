#include "task.h"

Task::Task(const unsigned int _id, const QString & _decription, const QString &_implementer,
     const QDate & _date):
    id(_id),
    decription(_decription),
    implementer(_implementer),
    date(_date){}


Task::Task()
{}
