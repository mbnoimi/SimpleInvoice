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
    
public:
    Ui::DialogNew *ui;

private:
    QSqlDatabase db_;
    QSqlQueryModel *model_;
    QStringList devices_, statuses_, models_;
    bool input_;
    int id_;

    void updateData();
    bool isValidDate(QDate in, QDate out);
};

#endif // DIALOGNEW_H
