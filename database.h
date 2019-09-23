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

using std::string;
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
void findRouteFastest(std::list<QString> * orderedCities, unsigned long numCities);

#endif // DATABASE_H
