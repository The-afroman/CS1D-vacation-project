﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <iostream>
#include "database.h"
#include "trippage.h"
#include "shortesttripwindow.h"
#include "customtrippage.h"
#include "numcities.h"
#include "login.h"

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
    "     border-color:black;"
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
    "     border-color:black;"
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
    "     border-color:black;"
    " }"

    "QPushButton#Trip3:hover:pressed"
    "{"
    "    background-color:red;"
    "}");

    }
    QString path = qApp->applicationDirPath();
    DbManager database(path + "/cities.db");

    //THIS CODE READS IN THE DATABASE AND EACH CITY ONLY ONCE TO LISTWIDGET
    //loadCityData(database);
    QSqlQuery query("SELECT DISTINCT start FROM citydata");
    int idStart = query.record().indexOf("start");
    while (query.next())
    {
        QString start = query.value(idStart).toString();
        ui->listWidget->addItem(start);
        totalCities++;
    }
    //database.printCities();
    //database.printFoods();

}

MainWindow::~MainWindow()
{
    for(int i = 0; i< ui->stackedWidget->count(); i++){
        delete pages[i];
    } //!< loopes through array to delete the pages of the stacked widget
    delete finalPage;
    delete[] pages;
    delete planner;
    delete ui;
    QApplication::quit();

}

/*! Will reset the stacked widget to its initail state*/
void MainWindow::resetStackW()
{
    ui->stackedWidget->setCurrentIndex(0);

    if(finalPage!=nullptr)
    {
        ui->stackedWidget->removeWidget(finalPage);
        delete finalPage;
        finalPage = nullptr;
    }
    if(planner!=nullptr)
    {
        ui->stackedWidget->removeWidget(planner);
        delete planner;
        planner = nullptr;
    }
    if(nCityDialog!=nullptr)
    {
        delete nCityDialog;
        nCityDialog=nullptr;
    }
    int count = ui->stackedWidget->count()-1;
    for(int i=0; i < count; i++)
    {
        ui->stackedWidget->removeWidget(pages[i]);
        delete pages[i];
        qDebug() << "\nnum widgets in SW: " << ui->stackedWidget->count() << endl;
    }
    delete[] pages;
}

/*! Creates the stacked widget for the shortest trip displaying all the information for each city page */
void MainWindow::on_Trip1_clicked()
{
    cout << "Planning new trip..." << endl;
    finalPage = new finalpage;

   //ShortestTripWindow shortestTripWindow;
   //shortestTripWindow.setModal(true);
   //shortestTripWindow.exec();

    QString temp;
    std::list<QString> * cities = new std::list<QString>;
    std::list<QString> * foodNames = new std::list<QString>;
    std::list<double> *  foodPrices = new std::list<double>;
    finalPage->setDistance(findRouteFastest(cities, 11, "Paris"));
    std::list<QString>::iterator it;
    pages = new tripPage*[cities->size()];
    int count = 0;

    listSize = (cities->size());
    for(it = cities->begin();it != cities->end();it++)
    {
        getFoodData(foodNames, foodPrices, *it);
        pages[count] = new tripPage;
        pages[count]->setTitle(*it);
        pages[count]->setFoodData(foodNames,foodPrices);
        if(count == 0){
            temp = "HIDE";
            pages[count]->setTextButtonOne(temp);
            temp = "NEXT CITY";
            pages[count]->setTextButtonTwo(temp);
        }
        else if(count == static_cast<int>(listSize)-1){
            temp = "PREVIOUS CITY";
            pages[count]->setTextButtonOne(temp);
            temp = "FINISH TRIP";
            pages[count]->setTextButtonTwo(temp);
            QObject::connect(pages[count], SIGNAL(finishTrip()), this, SLOT(tripFinish()));
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

/*! Uses signal and slots to access Trip2() */
void MainWindow::on_Trip2_clicked()
{
    cout << "Planning custom trip starting at london..." << endl;

    cout << "Planning new trip..." << endl;

    finalPage = new finalpage;
    nCityDialog = new numCities(nullptr, totalCities);
    QObject::connect(nCityDialog, SIGNAL(finish(int)), this, SLOT(Trip2(int)));
    nCityDialog->show();
}

/*! Creates the stacked widget for the custom trip starting at london displaying all the information for each city page */
void MainWindow::Trip2(int nCities)
{
    QString temp;
    std::list<QString> * cities = new std::list<QString>;
    std::list<QString> * foodNames = new std::list<QString>;
    std::list<double> *  foodPrices = new std::list<double>;
    finalPage->setDistance(findRouteFastest(cities, nCities, "London"));
    std::list<QString>::iterator it;
    pages = new tripPage*[cities->size()];
    int count = 0;

    listSize = (cities->size());
    for(it = cities->begin();it != cities->end();it++)
    {
        getFoodData(foodNames, foodPrices, *it);
        pages[count] = new tripPage;
        pages[count]->setTitle(*it);
        pages[count]->setFoodData(foodNames,foodPrices);
        if(count == 0){
            temp = "HIDE";
            pages[count]->setTextButtonOne(temp);
            temp = "NEXT CITY";
            pages[count]->setTextButtonTwo(temp);
        }
        else if(count == static_cast<int>(listSize)-1){
            temp = "PREVIOUS CITY";
            pages[count]->setTextButtonOne(temp);
            temp = "FINISH TRIP";
            pages[count]->setTextButtonTwo(temp);
            QObject::connect(pages[count], SIGNAL(finishTrip()), this, SLOT(tripFinish()));
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
        qDebug() << ui->stackedWidget->count() << " number of pages total." << endl;
        count++;
        qDebug() << "adding page for " << *it << endl;
        foodNames->clear();
        foodPrices->clear();
    }

    qDebug() << ui->stackedWidget->count() << " number of pages total." << endl;
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

/*! Uses signal and slots to access Trip3() */
void MainWindow::on_Trip3_clicked()
{
    planner = new customTripPage;
    finalPage = new finalpage;
    cout << "Planning totally custom trip..." << endl;
    QObject::connect(planner, SIGNAL(changetoPagePrev()), this, SLOT(pagePrevious()));
    QObject::connect(planner, SIGNAL(finish(std::list<QString> *)), this, SLOT(Trip3(std::list<QString> *)));
    //QObject::connect(planner, SIGNAL(changePageNext()), this, SLOT(nextPage()));
    ui->stackedWidget->addWidget(planner);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

/*! Creates the stacked widget for the custom trip displaying all the information for each city page */
void MainWindow::Trip3(std::list<QString> * initCities)
{
    QString temp;
    std::list<QString> * citiesList = new std::list<QString>;
    std::list<QString> * foodNames = new std::list<QString>;
    std::list<double> *  foodPrices = new std::list<double>;
    finalPage->setDistance(findRouteFastestCustom(citiesList, initCities));
    qDebug() << "CUSTOM ROUTE:\n\n";
    qDebug() << citiesList->front();
    qDebug() << initCities->front();
    std::list<QString>::iterator it;
    pages = new tripPage*[citiesList->size()];
    int count = 0;

    listSize = (citiesList->size());
    for(it = citiesList->begin();it != citiesList->end();it++)
    {
        getFoodData(foodNames, foodPrices, *it);
        pages[count] = new tripPage;
        pages[count]->setTitle(*it);
        pages[count]->setFoodData(foodNames,foodPrices);
        if(count == 0){
            temp = "HIDE";
            pages[count]->setTextButtonOne(temp);
            temp = "NEXT CITY";
            pages[count]->setTextButtonTwo(temp);
        }
        else if(count == static_cast<int>(listSize)-1){
            temp = "PREVIOUS CITY";
            pages[count]->setTextButtonOne(temp);
            temp = "FINISH TRIP";
            pages[count]->setTextButtonTwo(temp);
            QObject::connect(pages[count], SIGNAL(finishTrip()), this, SLOT(tripFinish()));
        }
        else{
            temp = "PREVIOUS CITY";
            pages[count]->setTextButtonOne(temp);
            temp = "NEXT CITY";
            pages[count]->setTextButtonTwo(temp);
        }
        QObject::connect(pages[count], SIGNAL(changePagePrev()), this, SLOT(pagePrevious()));
        QObject::connect(pages[count], SIGNAL(changePageNext()), this, SLOT(nextPage()));
        //QObject::connect(pages[count], SIGNAL(valueChanged(int)), this, SLOT(updatePrices(int)));
        ui->stackedWidget->addWidget(pages[count]);
        count++;
        qDebug() << "adding page for " << *it << endl;
        foodNames->clear();
        foodPrices->clear();
    }

    qDebug() << ui->stackedWidget->count() << " number of pages total." << endl;
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

/*! Moves to the previous city in the trip*/
void MainWindow::pagePrevious(){
    if(ui->stackedWidget->count() >= 2 && ui->stackedWidget->currentIndex() != 0){
         ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() -1);
         //qDebug() << "Current Page is: " << ui->stackedWidget->currentIndex() << endl;
    }
    else{
         //qDebug() << "Current Page is: " << ui->stackedWidget->currentIndex() << endl;
    }
}

/*! Moves to the next city in the trip*/
void MainWindow::nextPage(){
    if(ui->stackedWidget->count() > 1 && ui->stackedWidget->currentIndex() < ui->stackedWidget->count()){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
       // qDebug() << "Current Page is: " << ui->stackedWidget->currentIndex() << endl;
    }

    else{
        // qDebug() << "Current Page is: " << ui->stackedWidget->currentIndex() << endl;
    }

}

/*! Gets the information from the trip and opens up the final page and pases in the information*/
void MainWindow::tripFinish(){
    QObject::connect(finalPage, SIGNAL(backToMenu()), this, SLOT(resetStackW()));

    qDebug() << listSize << endl;
    double netTotal = 0;

    for(int i =0; i < static_cast<int>(listSize); i++){

        finalPage->addTreeItem(*pages[i]);
        netTotal += pages[i]->getTotal();

    }
    finalPage->setNetTotal(netTotal);

    ui->stackedWidget->addWidget(finalPage);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() +1);

}

/*! Opens login window and closes main window*/
void MainWindow::on_pushButton_clicked()
{
    login *w = new login(this);
    w->show();
    this->close();
}
