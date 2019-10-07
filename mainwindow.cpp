#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <iostream>
#include "database.h"
#include "trippage.h"
#include "shortesttripwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    /*hovering stylesheets*/
    {
    ui->Trip1->setStyleSheet(
    "   QPushButton#Trip1{"
    "     margin-left: 50px; margin-right: 50px;"
    "     background-color: rgb(146, 189, 108);"
    "     border-style: solid;"
    "     border-width: 2px;"
    "     border-color: beige;"
    "     font: bold 14px;"
    " }"
    " QPushButton#Trip1:pressed {"
    "     background-color: rgb(224, 0, 0);     "
    " }"
    " QPushButton#Trip1:hover {"
    "     background-color: rgb(224, 255, 0);"
    " }"

    "QPushButton#Trip1:hover:pressed"
    "{"
    "    background-color:red;"
    "}");
    ui->Trip2->setStyleSheet(
    "   QPushButton#Trip2{"
    "     margin-left: 50px; margin-right: 50px;"
    "     background-color: rgb(146, 189, 108);"
    "     border-style: solid;"
    "     border-width: 2px;"
    "     border-color: beige;"
    "     font: bold 14px;"
    " }"
    " QPushButton#Trip2:pressed {"
    "     background-color: rgb(224, 0, 0);     "
    " }"
    " QPushButton#Trip2:hover {"
    "     background-color: rgb(224, 255, 0);"
    " }"

    "QPushButton#Trip2:hover:pressed"
    "{"
    "    background-color:red;"
    "}");

    ui->Trip3->setStyleSheet(
    "   QPushButton#Trip3{"
    "     margin-left: 50px; margin-right: 50px;"
    "     background-color: rgb(146, 189, 108);"
    "     border-style: solid;"
    "     border-width: 2px;"
    "     border-color: beige;"
    "     font: bold 14px;"
    " }"
    " QPushButton#Trip3:pressed {"
    "     background-color: rgb(224, 0, 0);     "
    " }"
    " QPushButton#Trip3:hover {"
    "     background-color: rgb(224, 255, 0);"
    " }"

    "QPushButton#Trip3:hover:pressed"
    "{"
    "    background-color:red;"
    "}");

    }
    QString path = qApp->applicationDirPath();
    DbManager database(path + "/cities.db");
   // database.printFoods();

    //THIS CODE READS IN THE DATABASE AND EACH CITY ONLY ONCE TO LISTWIDGET
    //loadCityData(database);
    QSqlQuery query("SELECT DISTINCT start FROM citydata");
    int idStart = query.record().indexOf("start");
    while (query.next())
    {
        QString start = query.value(idStart).toString();
        ui->listWidget->addItem(start);
    }
    //database.printCities();
    //database.printFoods();

}

MainWindow::~MainWindow()
{
    for(int i = 0; i< ui->stackedWidget->count(); i++){
        delete pages[i];
    }
    delete pages;
    delete ui;

}

void MainWindow::on_Trip1_clicked()
{
    cout << "Planning new trip..." << endl;

   //ShortestTripWindow shortestTripWindow;
   //shortestTripWindow.setModal(true);
   //shortestTripWindow.exec();

    QString temp;
    std::list<QString> * cities = new std::list<QString>;
    std::list<QString> * foodNames = new std::list<QString>;
    std::list<double> *  foodPrices = new std::list<double>;
    findRouteFastest(cities, 11, "Paris");
    std::list<QString>::iterator it;
    pages = new tripPage*[11];
    int count = 0;

    int listSize = static_cast<int>(cities->size());
    for(it = cities->begin();it != cities->end();it++)
    {
        getFoodData(foodNames, foodPrices, *it);
        pages[count] = new tripPage;
        pages[count]->setTitle(*it);
        pages[count]->setFoodData(foodNames,foodPrices);
        if(count == 0){
            temp = "HIDE";
            pages[count]->setTextButtonOne(temp);
            temp ="NEXT CITY";
            pages[count]->setTextButtonTwo(temp);
        }
        else if(count == listSize-1){
            temp = "PREVIOUS CITY";
            pages[count]->setTextButtonOne(temp);
            temp = "FINISH TRIP";
            pages[count]->setTextButtonTwo(temp);
        }
        else{
            temp = "PREVIOUS CITY";
            pages[count]->setTextButtonOne(temp);
            temp = "NEXT CITY";
            pages[count]->setTextButtonTwo(temp);
        }
        QObject::connect(pages[count], SIGNAL(changePagePrev()), this, SLOT(pagePrevious()));
        QObject::connect(pages[count], SIGNAL(changePageNext()), this, SLOT(nextPage()));
        ui->stackedWidget->addWidget(pages[count]);
        count++;
        qDebug() << "adding page for " << *it << endl;
        foodNames->clear();
        foodPrices->clear();
    }

    qDebug() << ui->stackedWidget->count() << " number of pages total." << endl;
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::on_Trip2_clicked()
{
    cout << "Planning custom trip starting at london..." << endl;
}

void MainWindow::on_Trip3_clicked()
{
    cout << "Planning totally custom trip..." << endl;
}


void MainWindow::pagePrevious(){
    if(ui->stackedWidget->count() >= 2 && ui->stackedWidget->currentIndex() != 1){
         ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() -1);
         //qDebug() << "Current Page is: " << ui->stackedWidget->currentIndex() << endl;
    }
    else{
         //qDebug() << "Current Page is: " << ui->stackedWidget->currentIndex() << endl;
    }
}

void MainWindow::nextPage(){

    QString temp = pages[ui->stackedWidget->currentIndex()]->getTextButtonTwo();

    if(temp.compare("FINISH TRIP") == 0)
    {
         //write code to kersplato's final page ui;
        qDebug() << "Finishing Trip. " << endl;

    }
    else{
        if(ui->stackedWidget->count() > 1 && ui->stackedWidget->currentIndex() < ui->stackedWidget->count())
        {
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
           // qDebug() << "Current Page is: " << ui->stackedWidget->currentIndex() << endl;
        }
        else
        {
             qDebug() << "Current Page is: " << ui->stackedWidget->count() << endl;
        }
    }
}


