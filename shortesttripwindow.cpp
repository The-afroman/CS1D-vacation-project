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

void ShortestTripWindow::on_confirmTrip_clicked()
{

}
