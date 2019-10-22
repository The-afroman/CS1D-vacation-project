#include "customtrippage.h"
#include "ui_customtrippage.h"
#include "trippage.h"
#include "database.h"

customTripPage::customTripPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customTripPage)
{
    ui->setupUi(this);
    cities = new std::list<QString>;
    ui->addBtn->setMinimumSize(75,25);
    ui->removeBtn->setMinimumSize(75,25);
    ui->finishBtn->setMinimumSize(75,25);

    QSqlQuery query("SELECT DISTINCT start FROM citydata");
    int idStart = query.record().indexOf("start");
    while (query.next())
    {
        QString start = query.value(idStart).toString();
        ui->cityList->addItem(start);
    }


}

std::list<QString> * customTripPage::getCityList()
{
    return cities;
}

customTripPage::~customTripPage()
{
    delete ui;
}

/*! Adds the city that the user clicked on in the list widget to the list of cities for the users trip */
void customTripPage::on_addBtn_clicked()
{
    if(ui->cityList->currentItem() != nullptr)
    {
        QString city;
        city = ui->cityList->currentItem()->text();
        //qDebug() << city << '\n';
        ui->tripList->addItem(city);
        int row = ui->cityList->currentRow();
        ui->cityList->takeItem(row);
    }
}
/*
void customTripPage::on_backBtn_clicked()
{
    emit changetoPagePrev();
}
*/

/*! Puts the created trip list into the cities variable */
void customTripPage::on_finishBtn_clicked()
{
    for(int i = 0; i < ui->tripList->count(); i++)
    {
        auto item = ui->tripList->item(i);
        QString city = item->data(0).toString();
        cities->push_back(city);
    }

    std::list<QString>::iterator it;
    for(it = cities->begin(); it != cities->end(); it++)
    {
        qDebug() << *it << endl;
    }

    emit finish(cities);
}

/*! Removes a city that was added by the user to their trip list  */
void customTripPage::on_removeBtn_clicked()
{
    if(ui->tripList->currentItem() != nullptr)
    {
        ui->cityList->addItem(ui->tripList->currentItem()->text());
        int row = ui->tripList->currentRow();
        ui->tripList->takeItem(row);
    }
}
