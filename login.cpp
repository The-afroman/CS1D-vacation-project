#include "login.h"
#include "ui_login.h"
#include "QMessageBox"
#include "qdebug.h"
#include "mainwindow.h"
#include "admin.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_username->setText("test");
    ui->lineEdit_password_2->setText("test");

}

login::~login()
{
    delete ui;
}

/*! Displays login screen and takes the input for username and password from the user.
 * Allows access for a normal user and an admin user*/
void login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password_2->text();

    if(username ==  "test" && password == "test") {
         QMessageBox::information(this,QObject::tr("System Message"),tr("Login successful!"),QMessageBox::Ok);
         qDebug() << "SUCCESS";

         MainWindow *w = new MainWindow(this);
         this->close();
         w->show();

    }
    else if(username ==  "admin" && password == "admin") {
        QMessageBox::information(this,QObject::tr("System Message"),tr("Login successful!"),QMessageBox::Ok);
        qDebug() << "SUCCESS";
        admin *h =  new admin(this);
        this->close();
        h->show();
    }

    else {
        QMessageBox::information(this,QObject::tr("System Message"),tr("Login fail!"),QMessageBox::Ok);
        qDebug() << "FAILED";
    }
}
