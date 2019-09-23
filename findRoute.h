#ifndef FINDROUTE_H
#define FINDROUTE_H
#include "database.h"
#include <deque>


using std::deque;
using std::string;
/*
QString * findRoute(deque<QString> cities)
{
    QSqlQuery query("SELECT * FROM citydata");
    int idStart = query.record().indexOf("start");
    int idFinish = query.record().indexOf("finish");
    int idDistance = query.record().indexOf("distance");
    QString start = cities.front();
    QString finish;
    double distance;
    deque<QString> orderedCities;

    bool endSearch = false;

    while(query.next() && !endSearch)
    {
        if(query.value(idStart).toString() == start)
        {
            distance = query.value(idDistance).toDouble();
            endSearch = true;
        }
    }
    for(int i=0; i<10; i++)
    {
        if(query.value(idDistance).toDouble() < distance)
        {
            deque<QString>::iterator it = cities.begin();
            bool found = false;
            while(it != cities.end() && !found)
            {
                if(query.value(idFinish).toString() == *it)
                    found = true;
                    distance = query.value(idDistance).toDouble();
                    finish = query.value(idFinish).toString();
                it++;
            }
        }
        query.next();
    }
}
*/

bool checkCity(QString name, std::list<QString> * orderedCities)
{
    std::list<QString>::iterator it;
    for(it = orderedCities->begin();it != orderedCities->end(); it++)
    {
        if(*it == name)
            return false;
    }
    return true;
}

void findRouteFastest(QString start, std::list<QString> * orderedCities)
{
    QSqlQuery query;
    query.exec("SELECT * FROM citydata");
    int idStart = query.record().indexOf("start");
    int idFinish = query.record().indexOf("finish");
    int idDistance = query.record().indexOf("distance");
    QString finish;
    //I seriously couldn't think of anything better to do :(
    double distance = 100000;

    bool endSearch = false;

    while(!endSearch && query.next())
    {
        //qDebug() << query.value(idDistance).toDouble() << " " << query.value(idStart).toString() << " ";
        if(query.value(idStart).toString() == start)
        {
            endSearch = true;
        }
    }
    for(int i=0; i<10; i++)
    {

        //qDebug() << query.value(idDistance).toDouble() << " " << query.value(idFinish).toString() << " ";
        if(query.value(idDistance).toDouble() <= distance && checkCity(query.value(idFinish).toString(), orderedCities))
        {
            distance = query.value(idDistance).toDouble();
            finish = query.value(idFinish).toString();
        }
        query.next();
    }
    orderedCities->push_back(finish);
    if(orderedCities->size() < 11)
    {
        query.finish();
        findRouteFastest(finish, orderedCities);
    }
}
#endif // FINDROUTE_H
