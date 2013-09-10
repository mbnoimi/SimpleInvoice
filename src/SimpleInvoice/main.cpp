#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if !defined(Q_OS_ANDROID)
    a.setStyleSheet("* {font: 9pt \"Tahoma\";}");
#endif

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
#if defined(Q_OS_ANDROID)
    QString reportFile = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/report.xml";
    QString databaseFile = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/database.db";
#else
    QString reportFile = a.applicationDirPath()+"/report.xml";
    QString databaseFile = a.applicationDirPath()+"/database.db";
#endif
    if (!QFile::exists(reportFile)) {
        QFile::copy(":/templates/templates/report.xml", reportFile);
        settings.setValue("main/report", reportFile);
    }
    if (!QFile::exists(databaseFile))
        QFile::copy(":/templates/templates/database.db", databaseFile);
    QFile::setPermissions(reportFile,
                          QFile::WriteOwner|
                          QFile::ReadOwner|
//                          QFile::ExeOwner|
                          QFile::ReadUser|
                          QFile::WriteUser/*|
                          QFile::ExeUser*/
                          );
    QFile::setPermissions(databaseFile,
                          QFile::WriteOwner|
                          QFile::ReadOwner|
//                          QFile::ExeOwner|
                          QFile::ReadUser|
                          QFile::WriteUser|
//                          QFile::ExeUser|
                          QFile::ReadGroup|
                          QFile::WriteGroup|
//                          QFile::ExeGroup|
                          QFile::ReadOther|
                          QFile::WriteOther/*|
                          QFile::ExeOther*/
                          );

    MainWindow w;
    w.show();
    
    return a.exec();
}
