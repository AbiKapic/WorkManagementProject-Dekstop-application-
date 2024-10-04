#include "taskcreator.h"
#include "ui_taskcreator.h"

taskcreator::taskcreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskcreator)
{
    ui->setupUi(this);

    QSqlDatabase users_db;
        users_db = QSqlDatabase::addDatabase("QSQLITE","first"); // open the database with first connection
        users_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\users.db");
        if(!users_db.open()){
            qCritical() <<"Failed to open database.";

        }
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery *qry = new QSqlQuery(users_db);
         qry->prepare("select username from users"); // select only username from the users

         qry->exec(); // execute newly created query

         modal->setQuery(std::move(*qry)); // set a query to be able to set up listview

         ui->listView->setModel(modal); // setting up listview

}

taskcreator::~taskcreator()
{
    delete ui;
}

void taskcreator::on_pushButton_selected_clicked()
{
    QModelIndex index = ui->listView->currentIndex(); // select currently select member
    QString itemText = index.data(Qt::DisplayRole).toString();
    QStringListModel *model = new QStringListModel(this);

    list.append(itemText); // here we add it up to the list which is QStringList
    list.removeDuplicates(); // if there is any duplicated we will remove it

    model->setStringList(list); // set up model for the stringList
    ui->listView_2->setModel(model); // then here modify listView_2




}


void taskcreator::on_pushButton_clicked()
{

    QString name = ui->lineEdit->text(); // set up name from the lineEdit

    QString projectdescription = ui->textEdit->toPlainText(); // add up projectdescription
    projectdescription.remove("\n"); // remove all newlines for project description

    QString projectprogress = "0";


    QSqlDatabase prs_db;
    prs_db = QSqlDatabase::addDatabase("QSQLITE","second"); // open now second connection from projects
    prs_db.setDatabaseName("C:\\Users\\Comp\\Documents\\WorkManagementProject\\projects.db");
    if(!prs_db.open()){
        qCritical() <<"Failed to open database.";

    }
   //int i = 0;
    QString v = "";
    for(auto &items: list){ // go through the list of selected members and ad them to one string separated with whitespaces

        v = v+ items;
        v = v+ " ";

    }



   QSqlQuery qry(prs_db);

// here insert all of the members into the projects database
    qry.prepare("insert into projects (prname, prdesc, progress, members) values ('"+name +"', '"+projectdescription +"', '"+projectprogress +"', '"+v +"')");


     if(qry.exec()){
          QMessageBox::information(this,"CREATE","NEW TASK SAVED."); // if database is running fine we print the msg
           prs_db.close();

     }

     else{
         QMessageBox::information(this,"CREATE","THIS TASK ALREADY EXISTS."); // otherwise print error msg

        qDebug() << qry.lastError().text();
     }



            this->close();


}



