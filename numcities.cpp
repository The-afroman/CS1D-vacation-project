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

void numCities::on_pushButton_clicked()
{
    emit finish(cities);
    this->hide();
}

void numCities::on_spinBox_valueChanged(int arg1)
{
    cities = arg1;
}
