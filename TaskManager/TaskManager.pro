#-------------------------------------------------
#
# Project created by QtCreator 2018-01-06T18:36:34
#
#-------------------------------------------------

QT += core gui
QT += sql
QT += charts
QT += network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaskManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    dbmanager.cpp \
    task.cpp \
    networkmanager.cpp \
    Forms/mainwindow.cpp \
    Forms/addtaskdialog.cpp \
    Forms/exportsettings.cpp \
    Forms/addclientdialog.cpp

HEADERS += \
    dbmanager.h \
    task.h \
    networkmanager.h \
    Forms/mainwindow.h \
    Forms/addtaskdialog.h \
    Forms/exportsettings.h \
    Forms/addclientdialog.h

FORMS += \
    Forms/mainwindow.ui \
    Forms/addtaskdialog.ui \
    Forms/exportsrttings.ui \
    Forms/addclientdialog.ui
