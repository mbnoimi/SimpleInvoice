#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dateEdit_date->setDate(QDate::currentDate());
    // BUG: RTL issue!
    label_ = new QLabel;
    ui->statusBar->addPermanentWidget(label_);
    label_->show();

    dlgAbout_ = 0;
    dlgNew_ = 0;
    dlgOpen_ = 0;
    dlgSettings_ = 0;

    on_actionHome_triggered();

    connection();

#if !defined(Q_OS_ANDROID)
    ui->actionHome->setVisible(0);
#else
    ui->actionPrint->setVisible(0);
    ui->actionPrint_Preview->setVisible(0);
    ui->actionSaveAsPDF->setVisible(0);
    ui->mainToolBar->setIconSize(QSize(32, 32));
#endif
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
#if !defined(Q_OS_ANDROID)
    dlgNew_ = new DialogNew(db_, 1, this);
    dlgNew_->exec();
#else
    if (! dlgNew_) {
        dlgNew_ = new DialogNew(db_, 1, this);
        ui->stackedWidget->addWidget(dlgNew_);
        ui->stackedWidget->setCurrentWidget(dlgNew_);
        dlgNew_->ui->pushButton_cancel->setHidden(1);
        dlgNew_->ui->pushButton_ok->setHidden(1);
        dlgNew_->ui->line->setHidden(1);
        qDebug() << ui->stackedWidget->count();
    }
#endif
    updateData();
}

void MainWindow::on_actionOpen_triggered()
{
#if !defined(Q_OS_ANDROID)
    dlgOpen_ = new DialogNew(db_,
                             0,
                             this,
                             model_->record(ui->tableView->currentIndex().row()).value("id").toInt());
    dlgOpen_->exec();
#else
    if (! dlgOpen_) {
        dlgOpen_ = new DialogNew(db_,
                                 0,
                                 0,
                                 model_->record(ui->tableView->currentIndex().row()).value("id").toInt());
        ui->stackedWidget->addWidget(dlgOpen_);
        ui->stackedWidget->setCurrentWidget(dlgOpen_);
        dlgOpen_->ui->pushButton_cancel->setHidden(1);
    }
#endif
    updateData();
}

void MainWindow::on_actionSettings_triggered()
{
#if !defined(Q_OS_ANDROID)
    dlgSettings_ = new DialogSettings(this);
    dlgSettings_->exec();
#else
    if (!dlgSettings_) {
        dlgSettings_ = new DialogSettings;
        ui->stackedWidget->addWidget(dlgSettings_);
        ui->stackedWidget->setCurrentWidget(dlgSettings_);
        dlgSettings_->ui->pushButton_close->setHidden(1);
    }
#endif
}

void MainWindow::on_actionExit_triggered()
{
    if (isOpen()) {

    } else
        exit(-1);
}

void MainWindow::on_actionAbout_triggered()
{
#if !defined(Q_OS_ANDROID)
    dlgAbout_ = new DialogAbout(this);
    dlgAbout_->exec();
#else
    if (! dlgAbout_) {
        dlgAbout_ = new DialogAbout;
        ui->stackedWidget->addWidget(dlgAbout_);
        ui->stackedWidget->setCurrentWidget(dlgAbout_);
        dlgAbout_->ui->pushButton->setHidden(1);
    }
#endif
}

void MainWindow::connection()
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(dbPath());
    if (!isOpen()) {
        //FIXME: Don't forget to fix model issue for Android
#if !defined(Q_OS_ANDROID)
        QMessageBox::critical(this, tr("Error!"), tr("Unable to connect to the database!") );
#else
        ui->label_errorMessage->setText(tr("Unable to connect to the database!"));
        ui->stackedWidget->setCurrentWidget(ui->page_errors);
#endif
        on_actionExit_triggered();
    } else {
        db_.open();
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
#if defined(Q_OS_ANDROID)
    return QString("%1%2%3")
            .arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation))\
            .arg(QDir::separator())
            .arg("database.db");
#else
    return QString("%1%2%3")
            .arg(qApp->applicationDirPath())\
            .arg(QDir::separator())
            .arg("database.db");
#endif
}

void MainWindow::updateData()
{
    if (db_.isOpen()) {
        model_ = new QSqlQueryModel;
        model_->setQuery(query_table, db_);
        model_->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model_->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model_->setHeaderData(2, Qt::Horizontal, tr("Device"));
        model_->setHeaderData(3, Qt::Horizontal, tr("Description"));
        model_->setHeaderData(4, Qt::Horizontal, tr("Cost"));
        model_->setHeaderData(5, Qt::Horizontal, tr("Recived"));
        model_->setHeaderData(6, Qt::Horizontal, tr("Status"));
        model_->setHeaderData(7, Qt::Horizontal, tr("Note"));
        ui->tableView->setModel(model_);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();

        model_devices_ = new QSqlQueryModel;
        model_devices_->setQuery(query_devices, db_);
        ui->comboBox_device->setModel(model_devices_);

        model_statues_ = new QSqlQueryModel;
        model_statues_->setQuery(query_statues, db_);
        ui->comboBox_status->setModel(model_statues_);

        QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
        QSqlQuery query(query_sum, db_);
        query.next();
        label_->setText(QString(tr("%1 : Item(s) | Sum = %2 %3"))
                        .arg(model_->rowCount())
                        .arg(query.value(0).toString())
                        .arg(settings.value("main/currency", tr("L.D.")).toString()));
    }
}

void MainWindow::forDesktopOnly()
{
    ui->label_errorMessage->setText(tr("This feature is avaliable under Desktop operating systems only!"));
    ui->stackedWidget->setCurrentWidget(ui->page_errors);
}

void MainWindow::gotToMainWidget()
{
    ui->stackedWidget->setCurrentWidget(ui->page_main);
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
    model_->setQuery(query);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    label_->setText(QString(tr("%1 : Item(s)")).arg(model_->rowCount()));
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    on_actionOpen_triggered();
}

void MainWindow::on_actionPrint_triggered()
{
#if !defined(Q_OS_ANDROID)
    int id = model_->record(ui->tableView->currentIndex().row()).value("id").toInt();
    if (id > 0) {
        int copies = QInputDialog::getInt(this, tr("Copies"), tr("Input number of copies"), 1);
        if (copies > 0) {
            OpenrptRenderer render(db_);

            ParameterList params;
            params.append("invoice_id", id);

            QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
            QString reportFile = settings.value("main/report", qApp->applicationDirPath()+"/report.xml").toString();

            render.print(copies, reportFile, params);
        }
    }
#else
    forDesktopOnly();
#endif
}

void MainWindow::on_actionSaveAsPDF_triggered()
{
#if !defined(Q_OS_ANDROID)
    int id = model_->record(ui->tableView->currentIndex().row()).value("id").toInt();
    QString pdfPath = QFileDialog::getSaveFileName(this, tr("Select PDF path..."), ".", tr("PDF (*.pdf)"));
    if (id > 0 && !pdfPath.isEmpty()) {
        OpenrptRenderer render(db_);

        ParameterList params;
        params.append("invoice_id", id);

        QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
        QString reportFile = settings.value("main/reporkt", qApp->applicationDirPath()+"/report.xml").toString();

        render.printToPDF(pdfPath, reportFile, params);
    }
#else
    forDesktopOnly();
#endif
}

void MainWindow::on_actionPrint_Preview_triggered()
{
#if !defined(Q_OS_ANDROID)
    //TODO: Activate after supporting Qt print preview
    //    int id = model_->record(ui->tableView->currentIndex().row()).value("id").toInt();
    //    if (id > 0) {

    //        OpenrptRenderer render(db_);

    //        ParameterList params;
    //        params.append("invoice_id", id);

    //        QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
    //        QString reportFile = settings.value("main/report", qApp->applicationDirPath()+"/report.xml").toString();

    //        render.print(1, reportFile, params, 1);
    //    }
#else
    forDesktopOnly();
#endif
}

void MainWindow::on_actionHome_triggered()
{
    if (dlgAbout_) {
        delete dlgAbout_;
        dlgAbout_ = 0;
    }

    if (dlgNew_) {
        delete dlgNew_;
        dlgNew_ = 0;
    }

    if (dlgOpen_) {
        delete dlgOpen_;
        dlgOpen_ = 0;
    }

    if (dlgSettings_) {
        dlgSettings_->save();
        delete dlgSettings_;
        dlgSettings_ = 0;
    }

    ui->stackedWidget->setCurrentWidget(ui->page_main);
}

void MainWindow::on_pushButton_clicked()
{
    gotToMainWidget();
}
