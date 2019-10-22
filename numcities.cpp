#include "numcities.h"
#include "ui_numcities.h"
#include "database.h"

numCities::numCities(QWidget *parent, int maxSpinBox) :
    QWidget(parent),
    ui(new Ui::numCities)
{
    ui->setupUi(this);
    ui->spinBox->setRange(2, maxSpinBox);
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
