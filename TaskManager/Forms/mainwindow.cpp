#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings("config.ini", QSettings::IniFormat)
{
    ui->setupUi(this);
    dbManager = new DBManager(settings.value("DBFileName", "Tasks.db").toString());
    networkManager = new NetworkManager(settings.value("port", 49149).toInt(), dbManager);
    showTaskList(dbManager->loadTasks());
    dbManager->loadClients();
    networkManager->sendBase();
    networkManager->callBases();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    connect(dbManager, SIGNAL(error(QString)), this, SLOT(displayError(QString)));
    connect(networkManager, SIGNAL(error(QString)), this, SLOT(displayError(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask(const QString &description, const QString &implementer, const QDate &date, bool local)
{
    if (dbManager->addTask(description, implementer, date, local) != -1)
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        networkManager->sendTask(dbManager->getTasks().last());
        addRow(dbManager->getTasks().last(), ui->tableWidget->rowCount()-1);
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

}

void MainWindow::on_openAction_triggered()
{
    auto dbFileNAme = QFileDialog::getOpenFileName(this, "Открыть БД", "", "*.db");
    settings.setValue("DBFileName", dbFileNAme);
    delete dbManager;
    dbManager = new DBManager(dbFileNAme);
    networkManager->setDB(dbManager);
    showTaskList(dbManager->loadTasks());
    dbManager->loadClients();
}

void MainWindow::on_addButton_clicked()
{
    AddTaskDialog *addTaskDialog = new AddTaskDialog(this);
    addTaskDialog->show();
}

void MainWindow::showTaskList(QList<Task> tasks)
{
    auto it = tasks.begin();
    ui->tableWidget->setRowCount(tasks.length());
    for (int i = 0; i < tasks.length(); ++i)
    {
        addRow(*it, i);
        ++it;
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::addRow(const Task &task, int i)
{
    QTableWidgetItem *impItem = new QTableWidgetItem(task.implementer);
    impItem->setFlags(impItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *dateItem = new QTableWidgetItem(task.date.toString("dd.MM.yyyy"));
    dateItem->setFlags(dateItem->flags() ^ Qt::ItemIsEditable);
    QCheckBox *locItem = new QCheckBox();
    locItem->setChecked(task.local);
    locItem->setAttribute(Qt::WA_TransparentForMouseEvents);
    locItem->setFocusPolicy(Qt::NoFocus);
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(locItem);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);
    QTableWidgetItem *descItem = new QTableWidgetItem(task.description);
    descItem->setFlags(descItem->flags() ^ Qt::ItemIsEditable);
    ui->tableWidget->setItem(i, 0, impItem);
    ui->tableWidget->setItem(i, 1, dateItem);
    ui->tableWidget->setCellWidget(i, 2, widget);
    ui->tableWidget->setItem(i, 3, descItem);
}

void MainWindow::displayError(QString message)
{
    QMessageBox::warning(this, "Error", message, QMessageBox::Ok);
}

void MainWindow::on_expSettingsAction_triggered()
{
    ExportSettings *expSettings = new ExportSettings(dbManager, this);
    expSettings->show();
}

void MainWindow::on_settingsAction_triggered()
{

}
