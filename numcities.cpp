#include "numcities.h"
#include "ui_numcities.h"

numCities::numCities(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::numCities)
{
    ui->setupUi(this);
}

numCities::~numCities()
{
    delete ui;
}

/*! Completes the chosing of the number of cities*/
void numCities::on_pushButton_clicked()
{
    emit finish(cities);
    this->hide();
}

/*! Changes the number of cities by what was chosen by the user in the spin box*/
void numCities::on_spinBox_valueChanged(int arg1)
{
    cities = arg1;
}
