#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent,QString n) :
    QDialog(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);

    n_user = n;
    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second"); // open second connection

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db); // create new query

    QStringList l;
    QString prg = "0";
     if(qry->exec("select * from projects where progress='"+prg +"' ")){ // find any progress with 0 same as in admin

         while(qry->next()) {


            l.append(qry->record().value("prname").toString());
         }
     }
     QStringListModel *model = new QStringListModel(this);


     model->setStringList(l);
     ui->listView->setModel(model); // add projects with progress zero to listView

     QStringList l2;
     prg = "99";
     if(qry->exec("select * from projects where progress='"+prg +"' ")){ // then same for the projects with progress 99

         while(qry->next()) {


            l2.append(qry->record().value("prname").toString());
         }
     }
     QStringListModel *model2 = new QStringListModel(this);


     model2->setStringList(l2);
     ui->listView_3->setModel(model2); // here add it to the third list
     QString prg2 = "0";
     QStringList l3;
     if(qry->exec("select * from projects where progress!='"+prg +"' and progress !='"+prg2 +"'")){ // and then remaining projects will go to listview2

         while(qry->next()) {


            l3.append(qry->record().value("prname").toString());
         }
     }


         QStringListModel *model3 = new QStringListModel(this);


         model3->setStringList(l3);
         ui->listView_2->setModel(model3);




         // timeline
         QSqlDatabase uus_db;
         uus_db = QSqlDatabase::addDatabase("QSQLITE","third");

         uus_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\timeline.db"); // for the timeline it is easy just to open third connection
         if(!uus_db.open()){
             qCritical() <<"Failed to open database.";

         }

         QSqlQuery *qry2 = new QSqlQuery(uus_db);
       QStringList timeL;

       if(qry2->exec("select * from timeline ")){ // select text from timeline


           while(qry2->next()){


               ui->textEdit_3->append(qry2->record().value("message").toString()); // append all messages to textEdit_3

           }
       }




}

user::~user()
{
    delete ui;
}

void user::on_pushButton_2_clicked()
{
    QString n;
    QModelIndex index = ui->listView->currentIndex(); // any selected listVIew item should be able to show info of the project

    QString itemText = index.data(Qt::DisplayRole).toString();
   // QStringListModel *model = new QStringListModel(this);

    QModelIndex index2 = ui->listView_2->currentIndex();
    QString itemText2 = index2.data(Qt::DisplayRole).toString();

    QModelIndex index3 = ui->listView_3->currentIndex();
    QString itemText3 = index3.data(Qt::DisplayRole).toString();

    QStringList list; // in all 3 lists we are checking if any of the items is being selected
    if(itemText.length() > 0){
    list.append(itemText);
    }

    QStringList list2;
    if(itemText2.length() > 0){
    list2.append(itemText2);
    }

    QStringList list3;
    if(itemText3.length() > 0){
    list3.append(itemText3);
    }

    if(!list.empty()){
         n = itemText;
    }

    if(!list2.empty()){
         n = itemText2;
    }

    if(!list3.empty()){
         n = itemText3;
    }
    info1 = new info(this,n); // here we call the new info
    info1->show();
}


void user::on_pushButton_clicked()
{
    QString n;
    QModelIndex index = ui->listView->currentIndex(); // now similar process will happen if we want to update list

    QString itemText = index.data(Qt::DisplayRole).toString(); // read all the selected items from all 3 listviews


    QModelIndex index2 = ui->listView_2->currentIndex();
    QString itemText2 = index2.data(Qt::DisplayRole).toString();

    QModelIndex index3 = ui->listView_3->currentIndex();
    QString itemText3 = index3.data(Qt::DisplayRole).toString();

    QStringList list;
    if(itemText.length() > 0){ // then check in which lists they were being selected
    list.append(itemText);
    }

    QStringList list2;
    if(itemText2.length() > 0){
    list2.append(itemText2);
    }

    QStringList list3;
    if(itemText3.length() > 0){
    list3.append(itemText3);
    }

    if(!list.empty()){
         n = itemText; // set up n based on itemText
    }

    if(!list2.empty()){
         n = itemText2;
    }

    if(!list3.empty()){
         n = itemText3;
    }

    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second"); // chose second connection for the projects

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db); // create new query



    QString l;
    QString prg = "0";
     if(qry->exec("select * from projects where prname='"+n +"' ")){

         while(qry->next()) {


            l = (qry->record().value("members").toString()); // conver members list to string
         }
     }

       QStringList l1 = l.split(" "); // split text by whitespace so we get separate members

       bool check = 0;

       for(auto &item : l1) { // if user is able to update user needs to be assigned to that project

           if(item == n_user){ // we will find here if we are able to
               check = 1;
           }
       }


       if(check == 1){
            uus = new updateuser(this,n); // if user is able to update user needs to be assigned to that project
            uus->show();
       }

       else{

           QMessageBox::information(this,"Update","You were not assigned this project.");
       }


}


void user::on_pushButton_3_clicked()
{
    QSqlDatabase uus_db;
    uus_db = QSqlDatabase::addDatabase("QSQLITE","third");

    uus_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\timeline.db"); // for the timeline we will be able to update by clicking this button and update
    if(!uus_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry2 = new QSqlQuery(uus_db);
    QString msg = n_user + ": ";
    msg = msg + ui->lineEdit->text(); // set up msg

        qry2->prepare("insert into timeline (message) values ('"+msg +"')");
    if(qry2->exec()) { // we will insert into a timeline database msg

         QMessageBox::information(this,"Message","SAVED"); // if it was saved we will get the msg
         ui->lineEdit->clear();
    }
    else{
        QMessageBox::information(this,"Message","NOT SAVED"); // otherwise no msg

    }
}


void user::on_pushButton_4_clicked()
{
    QSqlDatabase uus_db;
    uus_db = QSqlDatabase::addDatabase("QSQLITE","third"); // open the third connection

    uus_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\timeline.db"); // to be able to update textEdit3
    if(!uus_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry2 = new QSqlQuery(uus_db);
  QStringList timeL;
  ui->textEdit_3->clear(); // first clear textEdit3

  if(qry2->exec("select * from timeline ")){


      while(qry2->next()){


          ui->textEdit_3->append(qry2->record().value("message").toString()); // then update it with newly updated database as well

      }
  }
}

