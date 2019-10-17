#include "numcitiesdialog.h"
#include "ui_numcitiesdialog.h"

numCitiesDialog::numCitiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::numCitiesDialog)
{
    ui->setupUi(this);
    ui->spinBox->setRange(2,11);
}

numCitiesDialog::~numCitiesDialog()
{
    delete ui;
}

void numCitiesDialog::on_numCitiesDialog_finished(int result)
{
    ui->spinBox->value();
}

void numCitiesDialog::on_numCitiesDialog_rejected()
{

}
