#ifndef ADMIN_H
#define ADMIN_H

#include <QFileInfo>
#include <QtDebug>
#include <QDialog>
#include <QtSql>

#include "taskcreator.h"
#include "updatet.h"
#include "info.h"

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr); // one constructor
    ~Admin(); // destructor

private slots:
    void on_pushButton_clicked(); // 5 private member functions for buttons

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Admin *ui; // we need createtask object, also update and info objects
    taskcreator* task;
    updatet *update1;
    info *info1;
    QString n; // name; // for the name of adming just for any case

};

#endif // ADMIN_H
