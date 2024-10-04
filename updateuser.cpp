#include "updateuser.h"
#include "ui_updateuser.h"

updateuser::updateuser(QWidget *parent,QString n) :
    QDialog(parent),
    ui(new Ui::updateuser)
{


    ui->setupUi(this);

    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second");

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db"); // open projects for the users to be able to update description
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db);
    //QStringList l3;
    if(qry->exec("select * from projects where prname='"+n +"'")){ // find any similar names of the project

        while(qry->next()) {


           ui->textEdit->setText(qry->record().value("prdesc").toString()); // here we set up textEdit
        }
    }
    name_project = n;
    n = "\t\t\t" + n;

      ui->lineEdit->setText(n);



}

updateuser::~updateuser()
{
    delete ui;
}

void updateuser::on_pushButton_clicked()
{
    QString description = ui->textEdit->toPlainText(); // read description



    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second");

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db"); // so to put it inside of the database updated version
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db);


    qry->prepare("update projects set prname='"+name_project+"', prdesc='"+description+"' where prname='"+name_project+"'"); // here we update the projects

    if(qry->exec()){
         QMessageBox::information(this,"Update","UPDATE SAVED."); // if everything checks we update it here
        prs_db.close();
    }

    else{
        QMessageBox::information(this,"Update","ERROR UPDATING."); // if not we print error


    }
     this->close();
}

