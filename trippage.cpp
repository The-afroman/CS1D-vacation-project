#include "trippage.h"
#include "ui_trippage.h"

tripPage::tripPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tripPage)
{
    ui->setupUi(this);
    foodNames = new list<QString>;
    foodPrices = new list<double>;
    ui->pushButton->setMinimumSize(150,50);
    ui->pushButton_2->setMinimumSize(150,50);
    cityTitle = new QLabel;
    cityTitle->setMinimumSize(200,100);
    cityTitle->show();
    ui->titleVBox->setAlignment(cityTitle, Qt::AlignHCenter);
    ui->titleVBox->setAlignment(Qt::AlignTop);


    ui->titleVBox->addWidget(cityTitle);
}


tripPage::~tripPage()
{
    delete ui;
}

void tripPage::initFoodUI(){
    int size = static_cast<int>(foodNames->size());
    foodNameLabels = new QLabel*[size];
    foodQtyBox = new QSpinBox*[size];
    std::list<QString>::iterator it;
    std::list<double>::iterator dit;
    int count = 0;
    QLabel temp;
    QFont serifFont("Times", 12, QFont::Bold);
    //qDebug() << "size of food list is apperantly: " <<  size << endl;
    for(int i = 0; i < size; i++){
        foodNameLabels[i] = new QLabel();
        foodNameLabels[i]->setGeometry(75,50,0,0);
        foodNameLabels[i]->setFont(serifFont);
        foodNameLabels[i]->show();
        ui->vboxLabel->addWidget(foodNameLabels[i]);
        //qDebug() << "added Label" << endl;

        foodQtyBox[i] = new QSpinBox();
        foodQtyBox[i]->setRange(0,10000);
        foodQtyBox[i]->setGeometry(25,25,0,0);
        foodQtyBox[i]->show();
        foodQtyBox[i]->setStyleSheet(
                                     "     margin-left: 50px; margin-right: 50px;"
                                     "     border-style: solid;"
                                     "     border-width: 2px;"
                                     "     border-color: black;"
                                     "     font: bold 14px;"
                                     );

        ui->vboxLabel->addWidget(foodQtyBox[i]);
        //qDebug() << "added QtyBox" << endl;
    }
    for(it = foodNames->begin(); it != foodNames->end(); it++){
        setFoodNameLabel(*it, count);
        //qDebug() << "Label for: " << *it;
        count++;
    }

    count = 0;
    for(dit = foodPrices->begin(); dit != foodPrices->end(); dit++){
        appendFoodLabel(*dit, count);
        count++;
    }

    //cout << "Finished adding food Labels." << endl;


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
    //qDebug() << ui->pushButton_2->text();
    if(ui->pushButton_2->text().compare("FINISH TRIP") == 0)emit finishTrip();
    else emit changePageNext();
    
    
}

void tripPage::setFoodNameLabel(const QString & text, int count){
    foodNameLabels[count]->setText("Name: " + text);
}

void tripPage::appendFoodLabel(const double & number, int count){
    foodNameLabels[count]->setText(foodNameLabels[count]->text() + QString::fromStdString("\nPrice: $" + to_string(number).substr(0, 4) + "\nQuantity to buy:"));
}

void tripPage::setTitle(QString & title){
    cityTitle->setText("City:\n" + title);
    QFont font("Bree Serif", 20);
    cityTitle->setFont(font);
}
QString tripPage::getTitle()const{
    return cityTitle->text();
}

QString tripPage::getTextButtonTwo()const{
    return ui->pushButton_2->text();
}

void tripPage::setFoodData(list<QString> *list1, list<double> *list2){

    foodNames = list1;
    foodPrices = list2;
    /*)
    list<QString>::iterator it;
    for(it = list1->begin(); it != list1->end(); it++){
        foodNames->push_back(*it);
    }
    list<double>::iterator dit;
    for(dit = list2->begin(); dit != list2->end(); dit++){
        foodPrices->push_back(*dit);
    }
    */
    initFoodUI();
}
