#ifndef TASKCREATOR_H
#define TASKCREATOR_H

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDialog>
#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>




namespace Ui {
class taskcreator;
}

class taskcreator : public QDialog
{
    Q_OBJECT

public:
    explicit taskcreator(QWidget *parent = nullptr);
    ~taskcreator();


private slots:
    void on_pushButton_selected_clicked();

    void on_pushButton_clicked();


private:
    Ui::taskcreator *ui;
    QStringList list;   //add only one list for the members as a prive attribute

};

#endif // TASKCREATOR_H
