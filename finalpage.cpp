#include "database.h"
#include "trippage.h"
#include "finalpage.h"
#include "ui_finalpage.h"
#include <QPixmap>

finalpage::finalpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finalpage)
{
    ui->setupUi(this);
    QString path = qApp->applicationDirPath();
    QPixmap pix(path + "/map of europe.jpg");
    ui->label_pic->setPixmap(pix.scaled(960, 622, Qt::KeepAspectRatio));
}


finalpage::~finalpage()
{
    delete ui;
}

void finalpage::setPages(tripPage ** data){
    pages = data;
}
void finalpage::on_finish_clicked()
{

}


