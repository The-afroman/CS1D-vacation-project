#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"
#include "removecity.h"

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;
}

void admin::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow(this);
    this->close();
    w->show();
}

void admin::on_pushButton_4_clicked()
{
    removecity *r = new removecity(this);
    this->close();
    r->show();
}