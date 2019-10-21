#ifndef DATABASE_H
#define DATABASE_H
#pragma once
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using std::string;
using namespace std;
/*
 * NOTE, tables are:
 *  cities table: start TEXT, finish TEXT, distance DOUBLE
 *  foods table : city TEXT, food TEXT, price NUMERIC
 *
 */

/*! Class to manage and store the data needed like cities and food. Uses an SQL Database */
class DbManager
{
public:
    DbManager(const QString& path);

    //! destructor
    ~DbManager();

    //! add another city to the database
    bool addCity(const QString&,  const QString&, const double&);

    //! add more food to the database
    bool addFood(const QString&, const QString&, const double&);

    //! outputs the cities
    void printCities();

    //! deletes data
    void eraseData();

    //! outputs the food
    void printFoods();

private:
    QSqlDatabase m_db; //!< variable for the database
};

//! Loads in city data from a file
void loadCityData(DbManager & db, QString filename);

//! checks the list of cities
bool checkCity(QString name, std::list<QString> * orderedCities);

//! used to find the first city in the list
QString findFirstCity();

//! returns the food data
void getFoodData(std::list<QString> * foodNames, std::list<double> * foodPrices, QString & cityName);

//! Finds the fastest route for fastest trip
double findRouteFastest(std::list<QString> * orderedCities, unsigned long numCities, QString startCity, double distance = 0);

//! Finds the fastest route for the custom trip
double findRouteFastestCustom(std::list<QString> * orderedCities, std::list<QString> * includedCities, double distance = 0);

#endif // DATABASE_H
