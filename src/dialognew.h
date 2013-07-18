#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include <QDialog>
#include <QtSql>
#include "queries.h"
#include <QtWidgets>

namespace Ui {
class DialogNew;
}

class DialogNew : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNew(QSqlDatabase database, bool isForInput, QWidget *parent = 0, int id = 0);
    ~DialogNew();
    
protected:
    void changeEvent(QEvent *e);
    
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();
    
private:
    Ui::DialogNew *ui;
    QSqlDatabase _db;
    QSqlQueryModel *_model;
    QStringList devices, statuses, models;
    bool _input;
    int _id;

    void updateData();
    bool isValidDate(QDate in, QDate out);
};

#endif // DIALOGNEW_H
