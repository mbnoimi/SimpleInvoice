#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlTableModel>
#include "queries.h"
#include "dialogabout.h"
#include "dialognew.h"
#include "dialogsettings.h"

MainWindow::MainWindow(QWidget* parent/*, Qt::WindowFlags fl*/) :
//    RenderWindow(parent, fl),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit_date->setDate(QDate::currentDate());
    // BUG: RTL issue!
    _label = new QLabel;
    ui->statusBar->addPermanentWidget(_label);
    _label->show();
    connection();
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
    DialogNew dlg(_db, 1, this);
    dlg.exec();
    updateData();
}

void MainWindow::on_actionOpen_triggered()
{
    DialogNew dlg(_db,
                  0,
                  this,
                  model->record(ui->tableView->currentIndex().row()).value("id").toInt());
    dlg.exec();
    updateData();
}

void MainWindow::on_actionSettings_triggered()
{
    DialogSettings dlg;
    dlg.exec();
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
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(dbPath());
    if (!isOpen()) {
        QMessageBox::critical(this, tr("Error!"), tr("Unable to connect to the database!"));
        on_actionExit_triggered();
    } else {
        _db.open();
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
    if (_db.isOpen()) {
        model = new QSqlQueryModel;
        model->setQuery(query_table, _db);
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Device"));
        model->setHeaderData(3, Qt::Horizontal, tr("Description"));
        model->setHeaderData(4, Qt::Horizontal, tr("Cost"));
        model->setHeaderData(5, Qt::Horizontal, tr("Recived"));
        model->setHeaderData(6, Qt::Horizontal, tr("Status"));
        model->setHeaderData(7, Qt::Horizontal, tr("Note"));
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();

        model_devices = new QSqlQueryModel;
        model_devices->setQuery(query_devices, _db);
        ui->comboBox_device->setModel(model_devices);

        model_statues = new QSqlQueryModel;
        model_statues->setQuery(query_statues, _db);
        ui->comboBox_status->setModel(model_statues);

        QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
        QSqlQuery query(query_sum, _db);
        query.next();
        _label->setText(QString(tr("%1 : Item(s) | Sum = %2 %3"))
                        .arg(model->rowCount())
                        .arg(query.value(0).toString())
                        .arg(settings.value("main/currency", tr("L.D.")).toString()));
    }
}

void MainWindow::print(int id, QString filePath)
{
    // TODO:
    //    QDir::setCurrent(qApp->applicationDirPath()+"/OpenRPT");
    //            qDebug() << "CurrentPath:" << QDir::currentPath();

    //    QStringList args;
    //    args << "-databaseURL=\"QSQLITE:///../database.db\""
    //         << "-noAuth"
    //         << "-close"
    //         << QString("-Param=invoice_id:string='%1'").arg(id)
    //         << "./reports/report.xml";

    //    if (filePath.isEmpty()) {
    //        args << "-print";
    //    } else {
    //        args << "-pdf"
    //             << QString("-outpdf=\"%1\"").arg(filePath);
    //    }
    //    if (!QProcess::startDetached(
    //            #ifdef Q_OS_WIN
    //                "./rptrender.bat"
    //            #else
    //                "./rptrender.sh"
    //            #endif
    //                , args)) {
    //        QMessageBox::critical(this, tr("Error!"), tr("Unable to load OpenRPT!"));
    //    }

//    fileOpen(":/reports/report.xml");
//    if (filePath.isEmpty()) {
//        // To printer
//        filePrint();
//    } else {
//        // To pdf file
//        filePrintToPDF(filePath);
//    }
}

void MainWindow::on_toolButton_cancel_clicked()
{
    updateData();
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
    _label->setText(QString(tr("%1 : Item(s)")).arg(model->rowCount()));
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    on_actionOpen_triggered();
}

void MainWindow::on_actionPrint_triggered()
{
    int id = model->record(ui->tableView->currentIndex().row()).value("id").toInt();
    if (id > 0) {
        print(id);
//        OpenrptRenderer oRender;
    }

}

void MainWindow::on_actionSaveAsPDF_triggered()
{
    int id = model->record(ui->tableView->currentIndex().row()).value("id").toInt();
    QString pdfPath = QFileDialog::getSaveFileName(this, tr("Select PDF path..."), ".", tr("PDF (*.pdf)"));
    if (id > 0 && !pdfPath.isEmpty()) {
        OpenrptRenderer render;
        render.fileOpen(":/reports/report.xml");
        render.filePrintToPDF(pdfPath, _db);
    }
}
