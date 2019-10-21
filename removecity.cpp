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
    QString start;
    DbManager database( path + "/cities.db");
    QSqlQuery query("SELECT DISTINCT start FROM citydata");
    int idStart = query.record().indexOf("start");
    while (query.next())
    {
        start = query.value(idStart).toString();
        ui->listWidget->addItem(start);
    }
}

removecity::~removecity()
{
    delete ui;
}

/*! Opens admin panel*/
void removecity::on_pushButton_2_clicked()
{
    admin *h =  new admin(this);
    this->close();
    h->show();
}

/*! Takes the city name clicked on from the list widget and puts it into
 * the cityname variable so it can be deleted */
void removecity::on_listWidget_itemPressed(QListWidgetItem *item)
{
    cityname=item->text();
}

/*! Deletes city from QSqlQuery query */
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
