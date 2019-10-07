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

void customTripPage::on_addBtn_clicked()
{
    QString city;
    city = ui->cityList->currentItem()->data(0).toString();
    qDebug() << city << '\n';
    ui->tripList->addItem(city);
}

void customTripPage::on_backBtn_clicked()
{
    emit changetoPagePrev();
}

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

void customTripPage::on_removeBtn_clicked()
{
    int row = ui->tripList->currentRow();
    ui->tripList->takeItem(row);
}
