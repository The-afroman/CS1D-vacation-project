#include "addfood.h"
#include "ui_addfood.h"
#include "database.h"
#include "admin.h"
#include "qdebug.h"

addfood::addfood(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addfood)
{
    ui->setupUi(this);
    QString path = qApp->applicationDirPath();
    QString start;
    DbManager database(path + "/cities.db");
    QSqlQuery query("SELECT DISTINCT start FROM citydata");
    int idStart = query.record().indexOf("start");
    while (query.next())
    {
        start = query.value(idStart).toString();
        ui->listWidget->addItem(start);
    }
}

addfood::~addfood()
{
    delete ui;
}

/*! Closes the curent window and opens the admin window again*/
void addfood::on_pushButton_2_clicked()
{
    admin *h =  new admin(this);
    this->close();
    h->show();
}

/*! Adds the name of the food and the price to the selected city name */
void addfood::on_pushButton_clicked()
{
   QString food= ui->plainTextEdit->toPlainText();
   QString price= ui->plainTextEdit_2->toPlainText();
   qDebug() << food;
   qDebug() << price;
   QSqlQuery query;
   query.prepare("INSERT INTO foods (city, food, price)"
                 "VALUES (?, ?, ?)");
   query.addBindValue(cityname);
   query.addBindValue(food);
   query.addBindValue(price);
   query.exec();
   query.finish();
}

/*! Takes the city name that was clicked on by user in the list widget
 * and puts it into the cityname variable so the food can be added to the city*/
void addfood::on_listWidget_itemClicked(QListWidgetItem *item)
{
    cityname=item->text();
}

