#include "trippage.h"
#include "ui_trippage.h"

tripPage::tripPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tripPage)
{
    ui->setupUi(this);

    ui->pushButton->setMinimumSize(150,50);
    ui->pushButton_2->setMinimumSize(150,50);
    cityTitle = new QLabel;
    cityTitle->setMinimumSize(200,100);
    cityTitle->show();
    ui->NameWindow->layout()->addWidget(cityTitle);
}


tripPage::~tripPage()
{
    delete ui;
}

void tripPage::setTextButtonOne(QString & text){
    if(text.compare("HIDE") == 0)ui->pushButton->hide();

    ui->pushButton->setText(text);
}

void tripPage::setTextButtonTwo(QString & text){
    if(text.compare("HIDE") == 0)ui->pushButton->hide();

    ui->pushButton_2->setText(text);
}

void tripPage::on_pushButton_clicked()
{
   emit changePagePrev();
}

void tripPage::on_pushButton_2_clicked()
{
    emit changePageNext();
}

void tripPage::setTitle(QString & title){
    cityTitle->setText(title);
}

const QString & tripPage::getTitle(){
    return cityTitle->text();
}
