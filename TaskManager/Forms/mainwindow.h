#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QSettings>
#include <QFileDialog>
#include "dbmanager.h"
#include "addtaskdialog.h"
#include "networkmanager.h"
#include "exportsettings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addTask(const QString & description, const QString & implementer, const QDate & date, bool local);
private slots:
    void on_openAction_triggered();

    void on_addButton_clicked();

    void on_expSettingsAction_triggered();

    void on_settingsAction_triggered();

public slots:
    void displayError(QString message);

private:
    Ui::MainWindow *ui;
    QSettings settings;
    DBManager *dbManager;
    NetworkManager *networkManager;
    void showTaskList(QList<Task> tasks);
    void addRow(const Task & task, int i);
};

#endif // MAINWINDOW_H
