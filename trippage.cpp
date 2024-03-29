#include "trippage.h"
#include "ui_trippage.h"

tripPage::tripPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tripPage)
{
    ui->setupUi(this);
    label1 = new QLabel("  Order Food: ");
    foodNames = new list<QString>;
    foodPrices = new list<double>;
    ui->pushButton->setMinimumSize(150,50);
    ui->pushButton_2->setMinimumSize(150,50);
    cityTitle = new QLabel;
    cityTitle->setMinimumSize(200,100);
    cityTitle->show();
    priceLabel = new QLabel("Amount Spent: ");
    priceLabel->setMinimumSize(200,100);
    priceLabel->show();
    //distanceSoFar = new QLabel("Distance So Far: ");
    //distanceSoFar->setMinimumSize(200,100);
    //distanceSoFar->show();
    ui->titleVBox->setAlignment(cityTitle, Qt::AlignHCenter);
    ui->titleVBox->setAlignment(Qt::AlignTop);
    ui->titleVBox->addWidget(cityTitle);
    ui->titleVBox->addWidget(priceLabel);
    //ui->titleVBox->addWidget(distanceSoFar);
}


tripPage::~tripPage()
{
    delete ui;
}

/*! Displays the names of the food items as labels and a food quantity
 * QSpinBox for each food item that can be used to change the amount desired
 * for purchase of a given food item */
void tripPage::initFoodUI(){
    sizeOfFoodLists = (foodPrices->size());
    qDebug() << "size of list is :" << sizeOfFoodLists << endl;
    foodNameLabels = new QLabel*[sizeOfFoodLists];
    foodQtyBox = new QSpinBox*[sizeOfFoodLists];
    std::list<QString>::iterator it;
    std::list<double>::iterator dit;
    int count = 0;
    QLabel temp;
    QFont serifFont("Times", 12, QFont::Bold);
    //qDebug() << "size of food list is apperantly: " <<  size << endl;
    label1->setFont(serifFont);
    label1->setStyleSheet("background-color: rgb(226, 255, 219);");
    ui->vboxLabel->addWidget(label1);
    for(int i = 0; i < static_cast<int>(sizeOfFoodLists); i++){
        hbox = new QHBoxLayout;
        tempW = new QWidget;
        foodNameLabels[i] = new QLabel();
        foodNameLabels[i]->setGeometry(75,50,0,0);
        foodNameLabels[i]->setFont(serifFont);
        foodNameLabels[i]->show();

        //qDebug() << "added Label" << endl;

        foodQtyBox[i] = new QSpinBox;
        foodQtyBox[i]->setRange(0, 100);
        foodQtyBox[i]->setGeometry(25,25,0,0);
        foodQtyBox[i]->show();
        foodQtyBox[i]->setStyleSheet(
                                     "     margin-left: 50px; margin-right: 50px;"
                                     "     border-style: solid;"
                                     "     border-width: 2px;"
                                     "     border-color: black;"
                                     "     font: bold 14px;"
                                     );
        hbox->addWidget(foodNameLabels[i]);
        hbox->addWidget(foodQtyBox[i]);
        tempW->setLayout(hbox);
        tempW->setStyleSheet("background-color: rgb(226, 255, 219);");

        connect(foodQtyBox[i], QOverload<const int>::of(&QSpinBox::valueChanged), this, &tripPage::on_valueChanged);

        ui->vboxLabel->addWidget(tempW);
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

void tripPage::on_valueChanged(){
    int i=0;
    total = 0;
    std::list<double>::iterator it;

    //THIS METHOD IS NOT WORKING THE FOOD PRICES ARE BEING RETURNED AS ZERO?
    //THE ABOVE ITERATOR WORKS AND APPENDS THE FOOD LABELS WITH CORRECT PRICES
    //TRY TO ITERATE THROUGH THE PRICES INSTEAD AND THEN CHECK TO SEE IF THE FOODQTYBOX
    //HAS A VALUE IN IT. 10/12/2019 @8:19
    //cout << sizeOfFoodLists << endl;
    string temp="";
    double tempD = 0;
    for(i=0; i < static_cast<int>(sizeOfFoodLists); i++){
        if(foodQtyBox[i]->value() >   0){
            temp = foodNameLabels[i]->text().toStdString();
            temp = temp.substr(temp.find("$")+1);
            tempD = stod(temp);
            total += tempD * foodQtyBox[i]->value();
        }
    }

    string originalText = priceLabel->text().toStdString();
    QString newText = QString::fromStdString(originalText.substr(0, originalText.find(":")+1));
    QString x = QString::number(total, 'f', 2);
    priceLabel->setText(newText + " $" + x);
}

double tripPage::getTotal()const{

    return total;
}

/*! Sets the button to either hidden or sets the text to say previous city */
void tripPage::setTextButtonOne(QString & text){
    if(text.compare("HIDE") == 0)ui->pushButton->hide();

    ui->pushButton->setText(text);
}

/*! Sets the button to either hidden or sets the text to say next city or finish trip */
void tripPage::setTextButtonTwo(QString & text){
    if(text.compare("HIDE") == 0)ui->pushButton->hide();

    ui->pushButton_2->setText(text);
}

/*! Gets called when Previous City button is clicked and goes back to the previous city in the trip*/
void tripPage::on_pushButton_clicked()
{
    emit changePagePrev();
}

/*! Gets called when Next City button is clicked or when the trip is finished it calls the finish trip function */
void tripPage::on_pushButton_2_clicked()
{
    //qDebug() << ui->pushButton_2->text();
    if(ui->pushButton_2->text().compare("FINISH TRIP") == 0)emit finishTrip();
    else emit changePageNext();
    
    
}

/*! Creates the name of the food labels for each food using the text and index passed to the function */
void tripPage::setFoodNameLabel(const QString & text, int count){
    foodNameLabels[count]->setText("Name: " + text);
}

/*! Adds price to the label for the food items using an index*/
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
    setFoodListSize(foodNames->size());
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

int tripPage::getFoodListSize()const{
    return static_cast<int>(sizeOfFoodLists);
}

void tripPage::setFoodListSize(unsigned long long value){
    sizeOfFoodLists = value;
}

QLabel ** tripPage::getFoodLabels()const{
    return foodNameLabels;
}

QSpinBox ** tripPage::getFoodQtyBox()const {
    return foodQtyBox;
}
list<QString> * tripPage::getFoodNames()const {
    return foodNames;
}
list<double> * tripPage::getFoodPrices()const{
    return foodPrices;
}
