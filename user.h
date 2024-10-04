#ifndef USER_H
#define USER_H

#include "updateuser.h"
#include "info.h"

#include <QtDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QDialog>
#include <QtSql>

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr,QString n = "Default");
    ~user();

private slots:
    void on_pushButton_2_clicked(); // 4 member functions that are private for buttons

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::user *ui;
    info *info1; // for user we need info of the dialog as well as the user string and one new object for the updateuserdialog
    QString n_user;
    updateuser *uus;
};

#endif // USER_H
