#include "dialogsettings.h"
#include "ui_dialogsettings.h"


DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
    ui->comboBox_language->setCurrentText(settings.value("main/lang", tr("English")).toString());
    ui->lineEdit_currency->setText(settings.value("main/currency", tr("L.D.")).toString());
    ui->lineEdit_reportPath->setText(settings.value("main/report", qApp->applicationDirPath()+"/report.xml").toString());
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::changeEvent(QEvent *e)
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

void DialogSettings::on_pushButton_close_clicked()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
    settings.setValue("main/lang", ui->comboBox_language->currentText());
    settings.setValue("main/currency", ui->lineEdit_currency->text());
    settings.setValue("main/report", ui->lineEdit_reportPath->text());
    close();
}

void DialogSettings::on_toolButton_browse_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select report file"), ".", "*.xml;;*.*");
    if (!filePath.isEmpty()) {
        ui->lineEdit_reportPath->setText(filePath);
    }
}
