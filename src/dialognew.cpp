#include "dialognew.h"
#include "ui_dialognew.h"

DialogNew::DialogNew(QSqlDatabase database, bool isForInput, QWidget *parent, QSqlRecord record) :
    QDialog(parent),
    ui(new Ui::DialogNew)
{
    ui->setupUi(this);
    db = database;
    model = new QSqlQueryModel;
    input = isForInput;
    p_record = record;
    if (input)
        setWindowIcon(QIcon(":/icons/res/document-new.png"));
    else
        setWindowIcon(QIcon(":/icons/res/document-open-folder.png"));
    updateData();
}

DialogNew::~DialogNew()
{
    delete ui;
}

void DialogNew::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogNew::updateData()
{
    ui->lineEdit_model->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_phone->clear();
    ui->lineEdit_serial->clear();
    ui->comboBox_device->clear();
    ui->comboBox_status->clear();
    ui->plainTextEdit_description->clear();
    ui->plainTextEdit_note->clear();
    ui->doubleSpinBox_cost->setValue(0);

    model->setQuery(query_devices, db);
    for (int var = 0; var < model->rowCount(); ++var) {
        QString data = model->record(var).value(0).toString();
        devices << data;
        ui->comboBox_device->addItem(data);
    }

    model->setQuery(query_statues, db);
    for (int var = 0; var < model->rowCount(); ++var) {
        QString data = model->record(var).value(0).toString();
        devices << data;
        ui->comboBox_status->addItem(data);
    }
    if (input) {
        ui->dateEdit_recived->setEnabled(1);
        ui->dateEdit_delivered->setEnabled(0);
        ui->dateEdit_recived->setDate(QDate::currentDate());
        ui->pushButton_add->setEnabled(1);
    } else {
        ui->dateEdit_delivered->setEnabled(1);
        ui->dateEdit_recived->setEnabled(0);
        ui->dateEdit_delivered->setDate(QDate::currentDate());
        ui->pushButton_add->setEnabled(0);
    }
}

void DialogNew::on_pushButton_ok_clicked()
{
    if (input) {
        on_pushButton_add_clicked();
        close();
    } else {

    }

}

void DialogNew::on_pushButton_add_clicked()
{
    QString query = query_add.arg(ui->lineEdit_name->text())
            .arg(ui->comboBox_device->currentText())
            .arg(ui->plainTextEdit_description->toPlainText())
            .arg(ui->doubleSpinBox_cost->value())
            .arg(ui->dateEdit_recived->date().toString("yyyy/MM/dd"))
            .arg(ui->plainTextEdit_note->toPlainText())
            .arg(ui->lineEdit_model->text())
            .arg(ui->lineEdit_serial->text())
            .arg(ui->dateEdit_delivered->date().toString("yyyy/MM/dd"))
            .arg(ui->lineEdit_phone->text())
            .arg(ui->comboBox_status->currentText());
    if (!ui->lineEdit_name->text().isEmpty()) {
        QSqlQuery qQuery(db);
        if (!qQuery.exec(query)) {
            QMessageBox::critical(this, tr("Error!"), tr("Unable to save the data to the database!"));
        } else
            updateData();
    } else
        QMessageBox::critical(this, tr("Error!"), tr("You need to input name of the invoice at least!"));
}
