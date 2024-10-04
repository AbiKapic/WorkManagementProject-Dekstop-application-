#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    QSqlDatabase prs_db; // create a database object
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second"); // then open it with the second connection which are projects

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){ // if openning failed print msg
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db); // create new query using dynamic allocation

    QStringList l; // a qstring list
    QString prg = "0";
     if(qry->exec("select * from projects where progress='"+prg +"' ")){ // select all projects where progress is 0 to add them to the first listview

         while(qry->next()) {

            l.append(qry->record().value("prname").toString()); // then add it to the list
         }
     }
     QStringListModel *model = new QStringListModel(this); // create a model for listview


     model->setStringList(l); // we append list to this model
     ui->listView->setModel(model); // create a model here for list view

     QStringList l2;
     prg = "99"; // now we will be checking for the third listview same way as for the first one
     if(qry->exec("select * from projects where progress='"+prg +"' ")){

         while(qry->next()) {

            l2.append(qry->record().value("prname").toString());
         }
     }
     QStringListModel *model2 = new QStringListModel(this);


     model2->setStringList(l2); // set a string list again to a model of l2 that we created for the third
     ui->listView_3->setModel(model2);
     QString prg2 = "0";
     QStringList l3; // now we will do remaining projects for the ones projects that are not for 0 or 100
     if(qry->exec("select * from projects where progress!='"+prg +"' and progress !='"+prg2 +"'")){

         while(qry->next()) {

            l3.append(qry->record().value("prname").toString());
         }
     }





         QStringListModel *model3 = new QStringListModel(this);


         model3->setStringList(l3);
         ui->listView_2->setModel(model3); // create a third listview2 model





}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_clicked()
{


    task = new taskcreator(this); // if we want to create a task we open a new object and dynamicaly allocate it



    task->show();




}
// C++ is both procedural and OOP
// C is procedural
// procedural, oop , functional( not used )

void Admin::on_pushButton_2_clicked() // remove task
{
    QModelIndex index = ui->listView->currentIndex(); // open the index of the current selected item

    QString itemText = index.data(Qt::DisplayRole).toString(); // get a selected item from the first list if it was selected

    QModelIndex index2 = ui->listView_2->currentIndex(); // same for listview2
    QString itemText2 = index2.data(Qt::DisplayRole).toString();

    QModelIndex index3 = ui->listView_3->currentIndex(); // same for listview3
    QString itemText3 = index3.data(Qt::DisplayRole).toString();

    QStringList list; // now append to the list itself any item we want to get for any of the lists
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



    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second"); // if we do succed we open the projects

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db); // here we open the new query

    qry->prepare("Delete from projects where prname='"+itemText +"'");
    if(qry->exec()){
        QMessageBox::information(this,"Delete","You have deleted project.Please update projects."); // and find any item in a database that is having itemText as
        // a prname and it will actually update

    }
    else{
        QMessageBox::critical(this,"Delete","Deletion not completed.");

    }

    }



    if(!list2.empty()){



    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second");

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db"); // open again for that if our list2 was not empty which means second list was selected
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db);

    qry->prepare("Delete from projects where prname='"+itemText2 +"'");
    if(qry->exec()){
        QMessageBox::information(this,"Delete","You have deleted project.Please update projects.");

    }
    else{
        QMessageBox::critical(this,"Delete","Deletion not completed.");

    }

    }


    if(!list3.empty()){ // also if list3 was not empty we would do the same




    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second");

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }

    QSqlQuery *qry = new QSqlQuery(prs_db);

    qry->prepare("Delete from projects where prname='"+itemText3 +"'");
    if(qry->exec()){
        QMessageBox::information(this,"Delete","You have deleted project.Please update projects.");

    }
    else{
        QMessageBox::critical(this,"Delete","Deletion not completed.");

    }

    }


}


void Admin::on_pushButton_3_clicked()
{

    QModelIndex index = ui->listView->currentIndex(); // similar as we did delete now we will do update thing

    QString itemText = index.data(Qt::DisplayRole).toString();

    QModelIndex index2 = ui->listView_2->currentIndex();
    QString itemText2 = index2.data(Qt::DisplayRole).toString();

    QModelIndex index3 = ui->listView_3->currentIndex();
    QString itemText3 = index3.data(Qt::DisplayRole).toString();

    QStringList list;
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
    // check all of the lists and then append if any exists and then if any of the lists is not empty we will add an itemtext to the n
    if(!list.empty()){
         n = itemText;
    }

    if(!list2.empty()){
         n = itemText2;
    }

    if(!list3.empty()){
         n = itemText3;
    }
    update1 = new updatet(this,n); // send n to a constructor of newly created updatedialog
    update1->show(); // open new window



}


void Admin::on_pushButton_4_clicked()
{  // same as for the update we will do also for the information of the task, if we want to check for an info we will simply press this button and all of info of
    // one project will be shown

    QModelIndex index = ui->listView->currentIndex();

    QString itemText = index.data(Qt::DisplayRole).toString();

    QModelIndex index2 = ui->listView_2->currentIndex();
    QString itemText2 = index2.data(Qt::DisplayRole).toString();

    QModelIndex index3 = ui->listView_3->currentIndex();
    QString itemText3 = index3.data(Qt::DisplayRole).toString();

    QStringList list;
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
    info1 = new info(this,n); // open new window for infodialog
    info1->show();
}



























void Admin::on_pushButton_5_clicked()
{
    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second"); // update all tasks button is going to update all of the tasks during run time

    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }
    QSqlQuery *qry = new QSqlQuery(prs_db);

    QStringList l;
    QString prg = "0";
     if(qry->exec("select * from projects where progress='"+prg +"' ")){ // so if there is any progress that is zero add it to first list

         while(qry->next()) {


            l.append(qry->record().value("prname").toString());
         }
     }
     QStringListModel *model = new QStringListModel(this);


     model->setStringList(l);
     ui->listView->setModel(model);

     QStringList l2;
     prg = "99";
     if(qry->exec("select * from projects where progress='"+prg +"' ")){ // any progress that is not zero and it is 99 add it to the third

         while(qry->next()) {


            l2.append(qry->record().value("prname").toString());
         }
     }
     QStringListModel *model2 = new QStringListModel(this);


     model2->setStringList(l2);
     ui->listView_3->setModel(model2);
     QString prg2 = "0";
     QStringList l3;
     if(qry->exec("select * from projects where progress!='"+prg +"' and progress !='"+prg2 +"'")){ // other ones to the second lsitview

         while(qry->next()) {


            l3.append(qry->record().value("prname").toString());
         }
     }





         QStringListModel *model3 = new QStringListModel(this);


         model3->setStringList(l3);
         ui->listView_2->setModel(model3);

}

