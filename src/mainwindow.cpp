#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlTableModel>
#include "queries.h"
#include "dialogabout.h"
#include "dialognew.h"
#include "dialogsettings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connection();
    ui->dateEdit_date->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionNew_triggered()
{
    DialogNew dlg(db, 1, this);
    dlg.exec();
    updateData();
}

void MainWindow::on_actionOpen_triggered()
{
    QSqlRecord record = model->record(ui->tableView->currentIndex().row());
    qDebug() << ui->tableView->currentIndex().data().toString()
             << record.value("name");
//    DialogNew dlg(db, 0, this);
//    dlg.exec();
//    updateData();
}

void MainWindow::on_actionSettings_triggered()
{
    /* DialogSettings dlg;
    dlg.exec()*/;
}

void MainWindow::on_actionExit_triggered()
{
    if (isOpen()) {

    } else
        exit(-1);
}

void MainWindow::on_actionAbout_triggered()
{
    DialogAbout dlg;
    dlg.exec();
}

void MainWindow::connection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath());
    if (!isOpen()) {
        QMessageBox::critical(this, tr("Error!"), tr("Unable to connect to the database!"));
        on_actionExit_triggered();
    } else {
        db.open();
        updateData();
    }
}

bool MainWindow::isOpen()
{
    if (QFile::exists(dbPath()))
        return 1;
    return 0;
}

QString MainWindow::dbPath()
{
    return QString("%1%2%3")
            .arg(qApp->applicationDirPath())\
            .arg(QDir::separator())
            .arg("database.db");
}

void MainWindow::updateData()
{
    if (db.isOpen()) {
        model = new QSqlQueryModel;
        model->setQuery(query_table, db);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();

        model_devices = new QSqlQueryModel;
        model_devices->setQuery(query_devices, db);
        ui->comboBox_device->setModel(model_devices);

        model_statues = new QSqlQueryModel;
        model_statues->setQuery(query_statues, db);
        ui->comboBox_status->setModel(model_statues);
    }
}

void MainWindow::on_toolButton_cancel_clicked()
{
    model->setQuery(query_table);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::on_toolButton_apply_clicked()
{
    int id = ui->tabWidget->currentIndex();
    QString query/* = query_filters*/;
    switch (id) {
    // name
    case 0:
        query = query_filters.arg("title").arg("%"+ui->lineEdit_name->text()+"%");
        break;
        // id
    case 1:
        query = query_filters.arg("id").arg(ui->spinBox_id->value());
        break;
        // date
    case 2:
        query = query_filters.arg("recived").arg(ui->dateEdit_date->date().toString("yyyy/MM/dd"));
        break;
        // device
    case 3:
        query = query_filters.arg("device").arg(ui->comboBox_device->currentText());
        break;
        // status
    case 4:
        query = query_filters.arg("status").arg(ui->comboBox_status->currentText());
        break;

    }
    model->setQuery(query);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::on_actionPrint_triggered()
{

}
