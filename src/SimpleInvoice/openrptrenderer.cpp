#include "openrptrenderer.h"


OpenrptRenderer::OpenrptRenderer()
    : QObject()
{
    qDebug() << "Hi from Static lib";
    _autoPrint = false;
}

void OpenrptRenderer::fileOpen(const QString &filename)
{
    QDomDocument doc;
    QString errMsg;
    int errLine, errColm;
    QFile file(filename);
    if(!doc.setContent(&file, &errMsg, &errLine, &errColm))
    {
        qDebug() << tr("Error Loading File")
                 <<tr("There was an error opening the file %1.\n\n%2 on line %3 column %4.")
                   .arg(filename).arg(errMsg).arg(errLine).arg(errColm);
        return;
    }

    QDomElement root = doc.documentElement();
    if(root.tagName() != "report")
    {
        qDebug() << tr("Not a Valid File")
                 << tr("The file %1 does not appear to be a valid file.\n\nThe root node is not 'report'.").arg(filename);
        return;
    }

    setDocument(doc);
}

void OpenrptRenderer::filePreview(int numCopies)
{
    print(true, numCopies);
}


void OpenrptRenderer::setDocument(const QDomDocument &doc)
{
    // Clear out the param list for this new document
    _params.clear();
    _lists.clear();

    QDomElement root = doc.documentElement();
    if(root.tagName() != "report")
    {
        qDebug() << tr("Not a Valid Report")
                 << tr("The report definition does not appear to be a valid report.\n\nThe root node is not 'report'.");
        return;
    }

    _doc = doc;

    for(QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        if(n.nodeName() == "parameter")
        {
            QDomElement elemSource = n.toElement();
            ORParameter param;

            param.name = elemSource.attribute("name");
            if(param.name.isEmpty())
                continue;

            param.type = elemSource.attribute("type");
            param.defaultValue  = elemSource.attribute("default");
            param.active = (elemSource.attribute("active") == "true");
            param.listtype = elemSource.attribute("listtype");

            QList<QPair<QString,QString> > pairs;
            if(param.listtype.isEmpty())
                param.description = elemSource.text();
            else
            {
                QDomNodeList section = elemSource.childNodes();
                for(int nodeCounter = 0; nodeCounter < section.count(); nodeCounter++)
                {
                    QDomElement elemThis = section.item(nodeCounter).toElement();
                    if(elemThis.tagName() == "description")
                        param.description = elemThis.text();
                    else if(elemThis.tagName() == "query")
                        param.query = elemThis.text();
                    else if(elemThis.tagName() == "item")
                        param.values.append(qMakePair(elemThis.attribute("value"), elemThis.text()));
                    else
                        qDebug("While parsing parameter encountered an unknown element: %s",elemThis.tagName().toLatin1().data());
                }
            }
            QVariant defaultVar;
            if(!param.defaultValue.isEmpty())
                defaultVar = QVariant(param.defaultValue);
            if("integer" == param.type)
                defaultVar = defaultVar.toInt();
            else if("double" == param.type)
                defaultVar = defaultVar.toDouble();
            else if("bool" == param.type)
                defaultVar = QVariant(defaultVar.toBool());
            else
                defaultVar = defaultVar.toString();
            QList<QPair<QString, QString> > list;
            if("static" == param.listtype)
                list = param.values;
            else if("dynamic" == param.listtype && !param.query.isEmpty())
            {
                QSqlQuery qry(param.query);
                while(qry.next())
                    list.append(qMakePair(qry.value(0).toString(), qry.value(1).toString()));
            }
            if(!list.isEmpty())
                _lists.insert(param.name, list);
        }
    }
}


void OpenrptRenderer::print(bool showPreview, int numCopies)
{
    ORPreRender pre;
    pre.setDom(_doc);
    ORODocument * doc = pre.generate();

    if(doc)
    {
        ReportPrinter printer(QPrinter::HighResolution);
#if QT_VERSION < 0x040700 // if qt < 4.7.0 then use the old function call.
        printer.setNumCopies( numCopies );
#else
        printer.setCopyCount( numCopies );
#endif
        if(!_printerName.isEmpty())
        {
            printer.setPrinterName(_printerName);
            _printerName = QString::null;
        }

        ORPrintRender render;
        render.setupPrinter(doc, &printer);

        if(showPreview)
        {
            if(printer.printerName().isEmpty())
            {
                QPrintDialog pd(&printer);
                if(pd.exec() != QDialog::Accepted)
                {
                    return; // no printer, can't preview
                }
            }
            PreviewDialog preview (doc, &printer);
            if (preview.exec() == QDialog::Rejected)
                return;
        }

        if(_autoPrint)
        {
            render.render(doc, &printer);
        }
        else
        {
            QPrintDialog pd(&printer);
            pd.setMinMax(1, doc->pages());
            if(pd.exec() == QDialog::Accepted)
            {
                render.render(doc, &printer);
            }
        }
        delete doc;
    }
}


void OpenrptRenderer::filePrintToPDF(QString &pdfFileName, QSqlDatabase database)
{

    // code taken from original code of the member [ void RenderWindow::filePrintToPDF() ]
    if(pdfFileName.isEmpty())
        return;

    if ( QFileInfo( pdfFileName ).suffix().isEmpty() )
        pdfFileName.append(".pdf");

    ORPreRender pre(database);
    pre.setDom(_doc);
    ORODocument *doc = pre.generate();
    if (doc) {
        ORPrintRender::exportToPDF(doc, pdfFileName);
        delete doc;
    }
}
