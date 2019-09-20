#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <iostream>
#include <fstream>
#include <QLayout>
using namespace std;

void loadCityData(DbManager &);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //I want to add hovering stylesheets to the buttons on the first screen dont know where to put this code

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

    DbManager database("C:/Users/bobby/Desktop/CS1D-vacation-project/testdb");

    loadCityData(database);
    //I tried implementing this function in Database.h
    //but ran into troubles when passing listWidget or the parent Widget into the db obj

    QSqlQuery query("SELECT * FROM cities2");
    int idStart = query.record().indexOf("start");
    int count = 10;
    while (query.next())
    {
        if(count %10 == 0 && count < 100){
            QString start = query.value(idStart).toString();
            ui->listWidget->addItem(start);
        }
        count++;
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}


void loadCityData(DbManager & db){

    ifstream input;
    input.open("C:/Users/bobby/Desktop/CS1D-vacation-project/data.csv");
    string startCity;
    string endCity;
    string distance;
    string dummyLine;

    if(input.is_open()){
        getline(input, dummyLine);
        while(!input.eof()){
           getline(input, startCity , ',');
           getline(input, endCity , ',');
           getline(input, distance , '\n');
           db.addCity(QString::fromStdString(startCity),QString::fromStdString(endCity), atof(distance.c_str()));
        }
    }
    else{
        std::cout << "Could not open data.csv" << endl;
    }
}

void MainWindow::on_pushButton_pressed()
{

}
