#include "addcity.h"
#include "ui_addcity.h"
#include "database.h"
#include "admin.h"
#include "qdebug.h"

addcity::addcity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addcity)
{
    ui->setupUi(this);
    QString path = qApp->applicationDirPath();
    DbManager database("C:/cities.db");
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

addcity::~addcity()
{
    delete ui;
}

void addcity::on_listWidget_itemClicked(QListWidgetItem *item)
{
     cityname=item->text();

}


void addcity::on_textBrowser_2_textChanged()
{
    ui->textBrowser_2->setText(cityname);
}
