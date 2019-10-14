#include "finalpage.h"
#include "ui_finalpage.h"

finalpage::finalpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::finalpage)
{
    ui->setupUi(this);

}


void finalpage::initUI(){

}

void finalpage::addTreeItems(const QList<QTreeWidgetItem *> items){
    ui->tripTree->addTopLevelItems(items);
}

finalpage::~finalpage()
{
    delete ui;
}
