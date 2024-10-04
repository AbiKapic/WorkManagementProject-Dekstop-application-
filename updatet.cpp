#include "updatet.h"
#include "ui_updatet.h"

updatet::updatet(QWidget *parent,QString n) :
    QDialog(parent),
    ui(new Ui::updatet)
{
    ui->setupUi(this);

    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second");

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db"); // create a second connection
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db);
    //QStringList l3;
    if(qry->exec("select * from projects where prname='"+n +"'")){ // find a specific project name

        while(qry->next()) {


           ui->textEdit->setText(qry->record().value("prdesc").toString()); // and set up textEdit with project description
        }
    }
    name_project = n;
    n = "\t\t\t" + n;

      ui->lineEdit->setText(n);
      if(qry->exec("select * from projects where prname='"+name_project +"'")){ // same goes with the progress and horizontal slider

          while(qry->next()) {

              ui->horizontalSlider->setSliderPosition(qry->record().value("progress").toInt());
              ui->progressBar->setValue(qry->record().value("progress").toInt());

          }
      }




}

updatet::~updatet()
{
    delete ui;
}




void updatet::on_pushButton_clicked()
{

    QString description = ui->textEdit->toPlainText(); // set up description string from a newly textEdit
    QString progress_value;
    progress_value.setNum(ui->horizontalSlider->value()); // same thing with the horizontal progress value



    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second"); // open second connection with projects

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db);


    qry->prepare("update projects set prname='"+name_project+"', prdesc='"+description+"', progress='"+progress_value+"' where prname='"+name_project+"'");
    // update query with newly set up description and progress

    if(qry->exec()){
         QMessageBox::information(this,"Update","UPDATE SAVED."); // if succeeded we will be able to say update saved
        prs_db.close();
    }

    else{
        QMessageBox::information(this,"Update","ERROR UPDATING."); // otherwise update was not saved


    }
     this->close();

}

