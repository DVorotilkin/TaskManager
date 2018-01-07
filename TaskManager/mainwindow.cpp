#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DBManager dbManager;
    dbManager.addTask("LLL", "III", QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}
