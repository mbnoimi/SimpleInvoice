#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if (QLocale::system().language() == QLocale::Arabic) {
        translator.load(":/langs/langs/ar.qm");
        a.installTranslator(&translator);
        a.setLayoutDirection(Qt::RightToLeft);
    } else {
        translator.load(":/langs/langs/en.qm");
        a.installTranslator(&translator);
        a.setLayoutDirection(Qt::LeftToRight);
    }

    MainWindow w;
    w.show();
    
    return a.exec();
}
