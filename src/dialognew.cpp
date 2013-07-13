#include "dialognew.h"
#include "ui_dialognew.h"

DialogNew::DialogNew(QSqlDatabase database, bool isForInput, QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::DialogNew)
{
    ui->setupUi(this);
    _db = database;
    _model = new QSqlQueryModel;
    _input = isForInput;
    _id = id;
    if (_input)
        setWindowIcon(QIcon(":/icons/res/document-new.png"));
    else
        setWindowIcon(QIcon(":/icons/res/document-open-folder.png"));
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
    ui->doubleSpinBox_cost->setSuffix(" "+settings.value("main/currency", tr("L.D.")).toString());
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
    ui->comboBox_device->clear();
    ui->comboBox_status->clear();
    _model->setQuery(query_devices, _db);
    for (int var = 0; var < _model->rowCount(); ++var) {
        ui->comboBox_device->addItem(_model->record(var).value(0).toString());
    }
    _model->setQuery(query_statues, _db);
    for (int var = 0; var < _model->rowCount(); ++var) {
        ui->comboBox_status->addItem(_model->record(var).value(0).toString());
    }

    if (_input) {
        ui->lineEdit_model->clear();
        ui->lineEdit_name->clear();
        ui->lineEdit_phone->clear();
        ui->lineEdit_serial->clear();
        ui->plainTextEdit_description->clear();
        ui->plainTextEdit_note->clear();
        ui->doubleSpinBox_cost->setValue(0);

        ui->dateEdit_recived->setDate(QDate::currentDate());
        ui->dateEdit_delivered->setDate(QDate::currentDate());

        ui->pushButton_add->setEnabled(1);
        ui->pushButton_delete->setEnabled(0);
        ui->dateEdit_recived->setEnabled(1);
        ui->dateEdit_delivered->setEnabled(0);
    } else {
        QString query = query_update_load.arg(_id);
        QSqlQuery qQuery(_db);
        if (!qQuery.exec(query)) {
            QMessageBox::critical(this, tr("Error!"), tr("Unable to load the data from the database!"));
            return;
        }
        while (qQuery.next()) {
            ui->lineEdit_model->setText(qQuery.value("model").toString());
            ui->lineEdit_name->setText(qQuery.value("title").toString());
            ui->lineEdit_phone->setText(qQuery.value("phone").toString());
            ui->lineEdit_serial->setText(qQuery.value("serial").toString());
            ui->comboBox_device->setCurrentText(qQuery.value("device").toString());
            ui->comboBox_status->setCurrentText(qQuery.value("status").toString());
            // BUG: RTL issue
            ui->plainTextEdit_description->setPlainText(qQuery.value("description").toString());
            ui->plainTextEdit_note->setPlainText(qQuery.value("note").toString());
            ui->doubleSpinBox_cost->setValue(qQuery.value("cost").toDouble());
            ui->dateEdit_recived->setDate(QDate::fromString(qQuery.value("recived").toString(), "yyyy/MM/dd"));
            ui->dateEdit_delivered->setDate(QDate::fromString(qQuery.value("sent").toString(), "yyyy/MM/dd"));
        }
        ui->pushButton_add->setEnabled(0);
        ui->pushButton_delete->setEnabled(1);
        ui->dateEdit_recived->setEnabled(0);
        ui->dateEdit_delivered->setEnabled(1);
    }
}

bool DialogNew::isValidDate(QDate in, QDate out)
{
    if( (in <= out) && (out <= QDate::currentDate()) )
        return 1;
    return 0;
}

void DialogNew::on_pushButton_ok_clicked()
{
    if (_input) {
        on_pushButton_add_clicked();
        close();
    } else {
        QString query = query_update.arg(ui->lineEdit_name->text())
                .arg(ui->comboBox_device->currentText())
                .arg(ui->plainTextEdit_description->toPlainText())
                .arg(ui->doubleSpinBox_cost->value())
                .arg(ui->dateEdit_recived->date().toString("yyyy/MM/dd"))
                .arg(ui->plainTextEdit_note->toPlainText())
                .arg(ui->lineEdit_model->text())
                .arg(ui->lineEdit_serial->text())
                .arg(ui->dateEdit_delivered->date().toString("yyyy/MM/dd"))
                .arg(ui->lineEdit_phone->text())
                .arg(ui->comboBox_status->currentText())
                .arg(_id);
        if (!ui->lineEdit_name->text().isEmpty() &&
                isValidDate(ui->dateEdit_recived->date(), ui->dateEdit_delivered->date())) {
            QSqlQuery qQuery(_db);
            if (!qQuery.exec(query)) {
                QMessageBox::critical(this, tr("Error!"), tr("Unable to save the data to the database!"));
            }
            close();
        } else
            QMessageBox::critical(this, tr("Error!"), tr("Missing name of invalid date!"));
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
        QSqlQuery qQuery(_db);
        if (!qQuery.exec(query)) {
            QMessageBox::critical(this, tr("Error!"), tr("Unable to save the data to the database!"));
        } else
            updateData();
    } else
        QMessageBox::critical(this, tr("Error!"), tr("You need to input name of the invoice at least!"));
}

void DialogNew::on_pushButton_delete_clicked()
{
    if (!_input) {
        if (QMessageBox::question(this, tr("Question"), tr("Do you want to delete this item?"), QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
            QString query = query_delete.arg(_id);
            QSqlQuery qQuery(_db);
            if (!qQuery.exec(query)) {
                QMessageBox::critical(this, tr("Error!"), tr("Unable to delete the item!"));
            }
            close();
        }
    }
}
