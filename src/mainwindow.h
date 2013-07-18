#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
//#include "OpenRPT/renderapp/renderwindow.h"
#include <renderwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : /*public QMainWindow
        ,*/ public RenderWindow
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

private:
    Ui::MainWindow *ui;
    QSqlDatabase _db;
    QSqlQueryModel *model, *model_devices, *model_statues;
    QLabel *_label;

    void connection();
    bool isOpen();
    QString dbPath();
    void updateData();
    void print(int id, QString filePath="");
};

#endif // MAINWINDOW_H
