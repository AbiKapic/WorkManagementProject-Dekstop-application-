#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
namespace Ui {
class info;
}

class info : public QDialog
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = nullptr,QString n = "Default");
    ~info();

private slots:
    void on_pushButton_clicked();

private:
    Ui::info *ui;
    QString name_project; // newly created QString for the name of project
};

#endif // INFO_H
