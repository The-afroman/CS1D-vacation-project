#include "database.h"
#include "shortesttripwindow.h"
#include "ui_shortesttripwindow.h"
#include <QtDebug>
#include <QPixmap>

ShortestTripWindow::ShortestTripWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortestTripWindow)
{
    ui->setupUi(this);
    QString path = qApp->applicationDirPath();
    QPixmap pix(path + "/map of europe.jpg");
    ui->label_pic->setPixmap(pix.scaled(960, 622, Qt::KeepAspectRatio));

}

ShortestTripWindow::~ShortestTripWindow()
{
    delete ui;
}

void ShortestTripWindow::on_confirmTrip_clicked()
{

    ui->orderedCityList->clear();

    //qDebug() << ui->spinBox1->value();
    ui->spinBox1->setRange(2,11);
    std::list<QString> * orderedCities = new std::list<QString>;
    double distanceTot = findRouteFastest(orderedCities, unsigned(long(ui->spinBox1->value())), "Paris");
    ui->label_2->setNum(distanceTot);

    std::list<QString>::iterator it;

    qDebug() << "START ORDERED CITIES\n";
    for(it = orderedCities->begin();it != orderedCities->end(); it++)
    {
        qDebug() << *it << " ";

        QString start = *it;
        ui->orderedCityList->addItem(start);
    }
}

