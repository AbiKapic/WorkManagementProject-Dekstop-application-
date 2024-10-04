#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMainWindow>
#include "admin.h"
#include "signup.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);



    void on_pushButton_signup_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;
    Admin* ads; // we need here 3 objects for ads sgs and usd objects to be able to manmipulate with them in different windows
    signup* sgs;
    user* usd;


};
#endif // MAINWINDOW_H
