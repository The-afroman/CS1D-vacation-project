#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"
#include "removecity.h"
#include "addfood.h"
#include "removefood.h"
#include "database.h"

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    //this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;

}

void admin::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow(this);
    w->show();
    this->close();
}

void admin::on_pushButton_4_clicked()
{
    removecity *r = new removecity(this);
    this->close();
    r->show();
}



void admin::on_pushButton_3_clicked()
{
    addfood *f = new addfood(this);
    this->close();
    f->show();
}

void admin::on_pushButton_5_clicked()
{
    removefood *j = new removefood(this);
    this->close();
    j->show();
}

void admin::on_pushButton_2_clicked()
{
    QString path = qApp->applicationDirPath();
    DbManager database(path + "/cities.db");
    QString filename = QFileDialog::getOpenFileName(this, tr("Pick a file"), tr("/home"),tr("Spread Sheets (*.csv *.xlsx)"));
    loadCityData(database, filename);
    qDebug() << filename;

}
