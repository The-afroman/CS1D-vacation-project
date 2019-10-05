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

void tripPage::initFoodUI(){
    int size = static_cast<int>(foodNames->size());
    foodNameLabels = new QLabel*[size];
    foodQtyBox = new QSpinBox*[size];
    std::list<QString>::iterator it;
    std::list<double>::iterator dit;
    int count = 0;
    QLabel temp;
    QFont serifFont("Times", 14, QFont::Bold);

    for(int i = 0; i < size; i++){
        foodNameLabels[i] = new QLabel;
        foodNameLabels[i]->setMinimumSize(200, 50);
        foodNameLabels[i]->setFont(serifFont);
        foodNameLabels[i]->show();
        ui->verticalLayout_2->addWidget(foodNameLabels[i]);

        foodQtyBox[i] = new QSpinBox;
        foodQtyBox[i]->setRange(0,10000);
        foodQtyBox[i]->setMinimumSize(25,25);
        foodQtyBox[i]->show();
        ui->verticalLayout_3->addWidget(foodQtyBox[i]);
    }
    for(it = foodNames->begin(); it != foodNames->end(); it++){
        setFoodNameLabel(*it, count);
        count++;
    }
    count = 0;
    for(dit = foodPrices->begin(); dit != foodPrices->end(); dit++){
        appendFoodLabel(*dit, count);
    }

    cout << "Finished adding food Labels." << endl;
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

void tripPage::setFoodNameLabel(const QString & text, int count){
    foodNameLabels[count]->setText(text);
}

void tripPage::appendFoodLabel(const double & number, int count){
    foodNameLabels[count]->setText(foodNameLabels[count]->text() + QString::fromStdString(" " + to_string(number)));
}

void tripPage::setTitle(QString & title){
    cityTitle->setText(title);
}
QString tripPage::getTitle()const{
    return cityTitle->text();
}

void tripPage::setFoodData(list<QString> *list1, list<double> *list2){
    foodNames = list1;
    foodPrices = list2;
    initFoodUI();
}
