#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>

#include "queries.h"
#include "dialogabout.h"
#include "dialognew.h"
#include "dialogsettings.h"

#include "ui_dialogabout.h"
#include "ui_dialognew.h"
#include "ui_dialogsettings.h"

#if !defined(Q_OS_ANDROID)
#include <openrptrenderer.h>
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void changeEvent(QEvent *e);
    
private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSettings_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_toolButton_cancel_clicked();

    void on_toolButton_apply_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionPrint_triggered();

    void on_actionSaveAsPDF_triggered();

    void on_actionPrint_Preview_triggered();

    void on_actionHome_triggered();

    void on_pushButton_clicked();

private:
    QSqlDatabase db_;
    QSqlQueryModel *model_, *model_devices_, *model_statues_;
    QLabel *label_;

    void connection();
    bool isOpen();
    QString dbPath();
    void updateData();

    void forDesktopOnly();
    void gotToMainWidget();

    DialogNew *dlgNew_, *dlgOpen_;
    DialogAbout *dlgAbout_;
    DialogSettings *dlgSettings_;

public:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
