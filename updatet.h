#ifndef UPDATET_H
#define UPDATET_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class updatet;
}

class updatet : public QDialog
{
    Q_OBJECT

public:
    explicit updatet(QWidget *parent = nullptr,QString n = "Default");

    ~updatet();

private slots:
    void on_pushButton_clicked();

private:
    Ui::updatet *ui;
    QString name_project; // for the update it is good to have name of the project so we can accept it via constructor

    int index;
};

#endif // UPDATET_H
