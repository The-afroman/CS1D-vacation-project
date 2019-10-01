#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <iostream>
#include "shortesttripwindow.h"
#include "database.h"
#include "trippage.h"

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

    //THIS CODE READS IN THE DATABASE AND EACH CITY ONLY ONCE TO LISTWIDGET
    //loadCityData(database);
    QSqlQuery query("SELECT * FROM citydata");
    int idStart = query.record().indexOf("start");
    int count = 10;
    while (query.next())
    {
        if(count %10 == 0 && count <= 110)
        {
            QString start = query.value(idStart).toString();
            ui->listWidget->addItem(start);
        }
        count++;
    }
    //database.printCities();
    //database.printFoods();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Trip1_clicked()
{
    cout << "Planning new trip..." << endl;

   // ShortestTripWindow shortestTripWindow;
   // shortestTripWindow.setModal(true);
   // shortestTripWindow.exec();

    QString path = qApp->applicationDirPath();
    DbManager database(path + "/cities.db");
    QSqlQuery query;
    std::list<QString> * cities = new std::list<QString>;
    findRouteFastest(cities, 11);
    std::list<QString>::iterator it;
    for(it = cities->begin();it != cities->end(); it++)
    {
        qDebug() << "adding page for " << *it << endl;
        ui->stackedWidget->addWidget(new tripPage(query, *it));
    }

    qDebug() << ui->stackedWidget->count() << " number of pages total." << endl;

}

void MainWindow::on_Trip2_clicked()
{
    cout << "Planning custom trip starting at london..." << endl;
}

void MainWindow::on_Trip3_clicked()
{
    cout << "Planning totally custom trip..." << endl;
}
