#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("* {font: 9pt \"Tahoma\";}");

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "GNU", "Simple Invoice");
    QString language = settings.value("main/lang", QObject::tr("English")).toString();

    QTranslator translator;
    if (language == QObject::tr("English")) {
        translator.load(":/langs/langs/en.qm");
        a.installTranslator(&translator);
        a.setLayoutDirection(Qt::LeftToRight);
    } else {
        translator.load(":/langs/langs/ar.qm");
        a.installTranslator(&translator);
        a.setLayoutDirection(Qt::RightToLeft);
    }

    MainWindow w;
    w.show();
    
    return a.exec();
}
