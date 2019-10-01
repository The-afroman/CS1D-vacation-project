#include "trippage.h"
#include <QLayout>

tripPage::tripPage( QWidget *parent): QWidget(parent)
{

    initUI();
}

void tripPage::initUI(){
    //SET UP THE LAYOUT AND GUI
    QGridLayout * gridL = new QGridLayout(this);

    back = new QPushButton("Back" , this);
    next = new QPushButton("Next", this);
}

tripPage::~tripPage()
{
    delete [] prices;
    delete [] foods;
    delete [] cityNames;
}
