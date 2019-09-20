#include "mainwindow.h"
#include <QApplication>
#include "database.h"
#include <iostream>
#include <fstream>
using namespace std;

void loadCityData(DbManager &);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DbManager test("C:/Users/bobby/Desktop/CS1D-vacation-project/testdb");
    //test.addCity("Paris", 100);
   // test.printCities();
    //cout << "deleting Data.." << endl;
   // test.eraseData();
    test.printCities();
    //loadCityData(test);

    return a.exec();
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
           getline(input, distance , ',');
           db.addCity(QString::fromStdString(startCity),QString::fromStdString(endCity), atof(distance.c_str()));
        }
    }
    else{
        std::cout << "Could not open data.csv" << endl;
    }
}
