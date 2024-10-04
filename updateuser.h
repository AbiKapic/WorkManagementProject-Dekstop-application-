#ifndef UPDATEUSER_H
#define UPDATEUSER_H

#include <QCoreApplication>

#include <QTextStream>
#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class updateuser;
}

class updateuser : public QDialog
{
    Q_OBJECT

public:
    explicit updateuser(QWidget *parent = nullptr,QString n = "Default");
    ~updateuser();

private slots:
    void on_pushButton_clicked();

private:
    Ui::updateuser *ui;
    QString name_project; // we just need one QString for the name of project
};

#endif // UPDATEUSER_H
