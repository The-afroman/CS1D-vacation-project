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

class DbManager
{
public:
    DbManager(const QString& path);
    bool addCity(const QString&,  const QString&, const double&);
    bool addFood(const QString&, const QString&, const double&);
    void printCities();
    void eraseData();
    void printFoods();
private:
    QSqlDatabase m_db;
};

bool checkCity(QString name, std::list<QString> * orderedCities);
QString findFirstCity();
void findRouteFastest(std::list<QString> * orderedCities, unsigned long numCities, QString startCity);
void findRouteFastestCustom(std::list<QString> * orderedCities, std::list<QString> * includedCities);

#endif // DATABASE_H
