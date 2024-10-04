#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_pushButton_signupdone_clicked();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
