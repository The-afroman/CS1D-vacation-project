#include "shortesttripwindow.h"
#include "ui_shortesttripwindow.h"
#include <QPixmap>

ShortestTripWindow::ShortestTripWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortestTripWindow)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/m3isa/OneDrive/Documents/CS1D Projects/map of europe.jpg");
    ui->label_pic->setPixmap(pix.scaled(960, 622, Qt::KeepAspectRatio));

}

ShortestTripWindow::~ShortestTripWindow()
{
    delete ui;
}

void ShortestTripWindow::on_showTrip_clicked()
{
<<<<<<< Updated upstream

=======
    ui->orderedCityList->clear();

    qDebug() << ui->spinBox1->value();
    ui->spinBox1->setRange(1,11);

    std::list<QString> * orderedCities = new std::list<QString>;
    findRouteFastest(orderedCities, ui->spinBox1->value());

    std::list<QString>::iterator it;

    qDebug() << "START ORDERED CITIES\n";
    for(it = orderedCities->begin();it != orderedCities->end(); it++)
    {
        qDebug() << *it << " ";

        QString start = *it;
        ui->orderedCityList->addItem(start);
    }
>>>>>>> Stashed changes
}
