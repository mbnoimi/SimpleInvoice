#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogSettings(QWidget *parent = 0);
    ~DialogSettings();
    
protected:
    void changeEvent(QEvent *e);
    
private slots:
    void on_pushButton_close_clicked();

    void on_toolButton_browse_clicked();

public:
    Ui::DialogSettings *ui;
    void save();
};

#endif // DIALOGSETTINGS_H
