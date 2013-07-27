#ifndef OPENRPTRENDERER_H
#define OPENRPTRENDERER_H
#include <QDebug>
#include <QtCore>
#include <QtWidgets>
#include <QtXml>
#include <QtSql>
#include <QtPrintSupport>

#include <../openrpt/common/xsqlquery.h>
#include <../openrpt/common/parameter.h>
#include <../openrpt/common/parameterproperties.h>
#include <../openrpt/common/data.h>
#include <../openrpt/common/parsexmlutils.h>
#include <../openrpt/common/paramlistedit.h>
#include <../openrpt/OpenRPT/renderer/renderobjects.h>
#include <../openrpt/OpenRPT/renderer/openreports.h>
#include <../openrpt/OpenRPT/renderer/orprerender.h>
#include <../openrpt/OpenRPT/renderer/orprintrender.h>
#include <../openrpt/OpenRPT/renderer/previewdialog.h>

class OpenrptRenderer : public QObject
{
    Q_OBJECT

public:
    OpenrptRenderer(QSqlDatabase database);
    void printToPDF(QString & pdfFileName , QString reportName, ParameterList params = ParameterList());
    void print(int numCopies, QString reportName, ParameterList params = ParameterList(), bool preview = 0);

    QString _printerName;
    bool _autoPrint;
    QString name();

protected:
    QMap<QString, QList<QPair<QString,QString> > > _lists;
    QDomDocument _doc;
    QMap<QString,QVariant> _params;

private:
    void print(bool showPreview, int numCopies);
    void openReport( const QString & filename );
    void setDocument( const QDomDocument & doc);
    QSqlDatabase _database;
};

#endif // OPENRPTRENDERER_H
