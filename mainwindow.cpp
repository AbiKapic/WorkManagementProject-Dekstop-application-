#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize) {

}



void MainWindow::on_pushButton_signup_clicked()
{






      sgs = new signup(this); // if we want signup we press button it will guide us there
      sgs->show();


}


void MainWindow::on_pushButton_login_clicked()
{

    QSqlDatabase users_db;
    users_db = QSqlDatabase::addDatabase("QSQLITE","first"); // open the database of users
    users_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\users.db");
    if(!users_db.open()){
        qCritical() <<"Failed to open database.";

    }

   QSqlQuery qry(users_db);



    QString login_password = ui->lineEdit_password->text(); // read password and user
    QString login_username = ui->lineEdit_username->text();

   int check = 0;
   if(qry.exec("select * from users where username='"+login_username +"' and password='"+login_password +"' and admin='"+"YES" +"'")){ // if it is admin in database
       int count = 0;
       while(qry.next()) {

       count++;
       }

       if(count == 1){ // if count is 1 that means this is admin
           users_db.close();

          QMessageBox::information(this,"Login","You logged in as an ADMIN."); // we print out that you logged in as adming and open the window of admin
          ads = new Admin(this);
          ads->show();
       }
       else{
           check++; // increase check so we know we were not here and username was not admins

       }

    }



   if(qry.exec("select * from users where username='"+login_username +"' and password='"+login_password +"' and admin='"+"NO" +"'")){ //same thing happens with user
       int count = 0;
       while(qry.next()) {

       count++;
       }

       if(count == 1){

          QMessageBox::information(this,"Login","You logged in as a USER."); // if it is user then we login like that
          users_db.close();

          usd = new user(this,login_username); // open user window
          usd->show();

       }
       else{
           check++;

       }

    }


   if(check == 2){
       QMessageBox::information(this,"Login","Wrong password or username."); // but if our check was 2 that means it was not either user or admin and we print wrong pass or username
       users_db.close();


   }



}

