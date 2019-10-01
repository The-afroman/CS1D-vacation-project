#include "removecity.h"
#include "ui_removecity.h"
#include "database.h"
#include "admin.h"
#include "qdebug.h"
removecity::removecity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removecity)
{
    ui->setupUi(this);
    QString path = qApp->applicationDirPath();
    DbManager database("C:/Users/Mohammed/Workspace/CS1D-vacation-project-master/cities.db");
    QSqlQuery query("SELECT * FROM citydata");
    int idStart = query.record().indexOf("start");
    int count = 10;
    while (query.next())
    {
        if(count %10 == 0 && count <= 110)
        {
            QString start = query.value(idStart).toString();
            ui->listWidget->addItem(start);
        }
        count++;
    }
}

removecity::~removecity()
{
    delete ui;
}

void removecity::on_pushButton_2_clicked()
{
    admin *h =  new admin(this);
    this->close();
    h->show();
}


void removecity::on_listWidget_itemPressed(QListWidgetItem *item)
{
    cityname=item->text();
}

void removecity::on_pushButton_clicked()
{
   qDebug() << cityname;
   QSqlQuery query;
   query.prepare("DELETE FROM citydata WHERE start= ?");
   query.addBindValue(cityname);
   query.exec();
   query.finish();
   query.prepare("DELETE FROM citydata WHERE finish = ?");
   query.addBindValue(cityname);
   query.exec();
   query.finish();

}
