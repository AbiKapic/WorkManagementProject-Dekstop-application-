#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent,QString n) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);


    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second"); // right at the beginning we want to open second connection

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db);

    if(qry->exec("select * from projects where prname='"+n +"'")){ // chose specific name for the project in this case we want to have this n from parameters

        while(qry->next()) {


           ui->textEdit->setText(qry->record().value("prdesc").toString()); // if we find any n's we will just update textEdit with a description
        }
    }
    name_project = n;
    n = "\t\t\t" + n;

      ui->lineEdit->setText(n);
      if(qry->exec("select * from projects where prname='"+name_project +"'")){ // then this part is for progress if we find same name as name_project in a database

          while(qry->next()) {

              ui->horizontalSlider->setSliderPosition(qry->record().value("progress").toInt()); // here we set up progressbar and horizontal slider
              ui->progressBar->setValue(qry->record().value("progress").toInt());

          }
      }


      QString str;
      if(qry->exec("select * from projects where prname='"+name_project +"'")){

          while(qry->next()) {

             str = qry->record().value("members").toString(); // same thing we will do for the members here and add it up firstly to string

          }
      }


      QStringList l = str.split(" "); // make a list and separate that string from database by whitespaces

      QStringListModel *model = new QStringListModel(this);



      model->setStringList(l);
      ui->listView->setModel(model); // set up listview with that list of members



}

info::~info()
{
    delete ui;
}

void info::on_pushButton_clicked()
{
    this->close(); // if we want to close we press button for closing
}

