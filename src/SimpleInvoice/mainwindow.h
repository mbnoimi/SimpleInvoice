#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
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

private:
    Ui::MainWindow *ui;
    QSqlDatabase _db;
    QSqlQueryModel *model, *model_devices, *model_statues;
    QLabel *_label;

    void connection();
    bool isOpen();
    QString dbPath();
    void updateData();

    void forDesktopOnly();
};

#endif // MAINWINDOW_H
