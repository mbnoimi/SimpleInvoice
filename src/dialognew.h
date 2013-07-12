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
    explicit DialogNew(QSqlDatabase database, bool isForInput, QWidget *parent = 0, QSqlRecord record = QSqlRecord());
    ~DialogNew();
    
protected:
    void changeEvent(QEvent *e);
    
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::DialogNew *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    QStringList devices, statuses, models;
    bool input;
    QSqlRecord p_record;

    void updateData();
};

#endif // DIALOGNEW_H
