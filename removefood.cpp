#include "removefood.h"
#include "ui_removefood.h"
#include "database.h"
#include "admin.h"
#include "qdebug.h"

removefood::removefood(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removefood)
{
    ui->setupUi(this);
    QString path = qApp->applicationDirPath();
   DbManager database(path + "/cities.db");
    QSqlQuery query("SELECT food FROM foods");
    int idStart = query.record().indexOf("food");
    int count = 10;
    while (query.next())
    {
        if(count <= 110)
        {
            QString start = query.value(idStart).toString();
            ui->listWidget->addItem(start);
        }
        count++;
    }
}


removefood::~removefood()
{
    delete ui;
}

/*! updates the price of the selected food */
void removefood::on_pushButton_clicked()
{
    qDebug() << foodname;
    QSqlQuery query;
    QString price = ui->lineEdit->text();
    query.prepare("UPDATE foods SET price = :newprice WHERE food = ?");
    query.addBindValue(foodname);
    query.bindValue(":newprice", price);
    query.exec();
    query.finish();

}
/*! Takes the food item clicked on in the list widget at puts it into the foodname variable so it can be deleted*/
void removefood::on_listWidget_itemClicked(QListWidgetItem *item)
{
    foodname=item->text();
}

/*! Opens the admin panel*/
void removefood::on_pushButton_2_pressed()
{
    admin *h =  new admin(this);
    this->close();
    h->show();
}

/*! removes the food from query */
void removefood::on_pushButton_3_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE from foods WHERE food = ?");
    query.addBindValue(foodname);
    query.exec();
    query.finish();
}

void removefood::on_plainTextEdit_textChanged()
{

}
