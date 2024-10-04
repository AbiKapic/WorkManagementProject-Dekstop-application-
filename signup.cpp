#include "signup.h"
#include "ui_signup.h"
signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
}

signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_signupdone_clicked()
{
    QString login_password = ui->lineEdit_pass1->text(); // for the sign up window we need to load in login password username and confirm password texts
    QString login_username = ui->lineEdit_user1->text(); // to our qStrings
    QString login_passwordconfirm = ui->lineEdit_cpass1->text();

    if(login_password == login_passwordconfirm) { // first check if passwords are matching


        QSqlDatabase users_db;
        users_db = QSqlDatabase::addDatabase("QSQLITE","first");
        users_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\users.db"); // open one of the first connections for the users
        if(!users_db.open()){
            qCritical() <<"Failed to open database.";

        }

       QSqlQuery qry(users_db);
        qry.prepare("insert into users (username, password, admin) values ('"+login_username +"', '"+login_password +"', '"+"NO" +"')"); // then if all is valid
// inser them into the database users
         if(qry.exec()){
              QMessageBox::information(this,"Save","SIGN UP SAVED."); // if everything is fine you just confirm it that it is fine
             users_db.close();
         }

         else{
             QMessageBox::information(this,"Save","Username already exists.");


         }


    this->close(); // close after that sign up
    }

    else {


        QMessageBox::information(this,"ERROR","Passwords do not match."); // if passwords do not match
    }



}

