﻿#include "database.h"


DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);
   //m_db.open();
   if (!m_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }

/*
USED THIS TO CREATE THE TABLE BUT YOU ONLY NEED TO CREATE IT ONCE SOOOOOOO

QSqlQuery query("CREATE TABLE citydata (start TEXT, finish TEXT, distance DOUBLE)");
if(!query.isActive())
    qWarning() << "ERROR: " << query.lastError().text();
else{
    qDebug() << "Created new Table" << endl;
    query.isActive();
    }
*/
}
DbManager::~DbManager(){

}

/*! Adds cities using QSqlQuery */
bool DbManager::addCity(const QString& start, const QString& finish, const double& distance)
{
    bool success = false;
    // you should check if args are ok first...
    QSqlQuery query;
    query.prepare("INSERT INTO citydata (start, finish, distance) VALUES (:start, :finish, :distance)");
    query.bindValue(":start", start);
    query.bindValue(":finish", finish);
    query.bindValue(":distance", distance);
    if(query.exec())
    {
       success = true;
    }
    else
    {
        qDebug() << "city add error:  "
                 << query.lastError();
    }

    return success;
}

/*! Adds food using QSqlQuery */
bool DbManager::addFood(const QString & city, const QString & food, const double & price)
{
    bool success = false;
    //err checking needed
    QSqlQuery query;
    query.prepare("INSERT INTO foods (city, food, price) VALUES (:city, :food, :price)");
    query.bindValue(":city", city);
    query.bindValue(":food", food);
    query.bindValue(":price", price);
    if(query.exec())
    {
       success = true;
    }
    else
    {
        qDebug() << "food add error:  "
                 << query.lastError();
    }

    return success;
}


/*! Displays cities*/
void DbManager::printCities(){
    QSqlQuery query("SELECT * FROM citydata");
    int idStart = query.record().indexOf("start");
    int idFinish = query.record().indexOf("finish");
    int idDistance = query.record().indexOf("distance");
    while (query.next())
    {
       QString start = query.value(idStart).toString();
       QString finish = query.value(idFinish).toString();
       int distance = query.value(idDistance).toInt();
       qDebug() <<  start << "," << finish << "," << distance << endl << endl;
    }
}

/*! Displays food*/
void DbManager::printFoods(){
    QSqlQuery query("SELECT * FROM foods");
    int idStart = query.record().indexOf("city");
    int idFinish = query.record().indexOf("food");
    int idDistance = query.record().indexOf("price");
    while (query.next())
    {
       QString city = query.value(idStart).toString();
       QString food = query.value(idFinish).toString();
       double price = query.value(idDistance).toDouble();
       qDebug() <<  city << "," << food << "," << price << endl << endl;
    }
}

/*! Deletes data using query */
void DbManager::eraseData(){
    QSqlQuery query;
    query.prepare("DELETE FROM citydata");
    query.exec();
}

/*! Loads in the city data from a specified file found in the computer*/
void loadCityData(DbManager & db, QString filename){
    std::ifstream input;
    input.open(filename.toStdString());
    std::string startCity;
    std::string endCity;
    std::string distance;
    std::string dummyLine;

    if(input.is_open()){
        getline(input, dummyLine);
        while(!input.eof()){
           getline(input, startCity , ',');
           getline(input, endCity , ',');
           getline(input, distance);

           if(startCity != "")
           {
               qDebug() << QString::fromStdString(startCity) + " "
                        << QString::fromStdString(endCity) + " "
                        << QString::fromStdString(distance);
               db.addCity(QString::fromStdString(startCity),QString::fromStdString(endCity), atof(distance.c_str()));
            }
        }
    }
    else{
        std::cout << "Could not open file" << std::endl;
    }
}

/*! Checks to see if the name of the city is allready in the list or not */
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

/*! Finds the shortest first trip and makes that the starting city */
QString findFirstCity()
{
    QSqlQuery query;
    query.exec("SELECT start, MIN(distance) FROM citydata");
    query.first();
    return query.value(0).toString();
}

/*! Returns the food data including the name of the food and its price */
void getFoodData(std::list<QString> * foodNames, std::list<double> * foodPrices, QString & cityName){
    QSqlQuery query;
    QString city = cityName;
    query.prepare("SELECT * FROM foods WHERE city= ?");
    query.addBindValue(city);
    query.exec();
    int idFood = query.record().indexOf("food");
    int idPrice = query.record().indexOf("price");
    while (query.next())
    {

       QString food = query.value(idFood).toString();
       double price = query.value(idPrice).toDouble();
       foodNames->push_back(food);
       foodPrices->push_back(price);
    }
}

/*! Finds the fastest route given the parameters like starting city and number of cities*/
double findRouteFastest(std::list<QString> * orderedCities, unsigned long numCities, QString startCity, double distance)
{
    QSqlQuery query;

    //query.exec("SELECT MAX(distance) FROM citydata");
    //query.first();
    //double distance = query.value(0).toDouble();
    //qDebug() << distance <<"\n\n";
    //query.exec("SELECT COUNT(DISTINCT start) FROM citydata");
    //query.first();
    //int cities = query.value(0).toInt();
    //qDebug() << cities <<endl <<endl;

    query.prepare("SELECT * FROM citydata WHERE start= ? ORDER by distance ASC");
    QString start;
    if(orderedCities->size() == 0)
    {
        start = startCity;
        distance = 0;
        orderedCities->push_back(start);
    }
    else
    {
        start = orderedCities->back();
    }
    query.addBindValue(start);
    query.exec();
    //int idStart = query.record().indexOf("start");
    int idFinish = query.record().indexOf("finish");
    int idDistance = query.record().indexOf("distance");
    QString finish;
    bool endSearch = false;

    while(!endSearch && query.next())
    {
        if(checkCity(query.value(idFinish).toString(), orderedCities))
        {
            distance += query.value(idDistance).toDouble();
            finish = query.value(idFinish).toString();
            endSearch = true;
        }
    }
    orderedCities->push_back(finish);
    if(orderedCities->size() < numCities)
    {
        query.finish();
        return findRouteFastest(orderedCities, numCities, startCity, distance);
    }
    else
    {
        return distance;
    }
}

/*! Finds the fastest route starting from the first city which is the first city in the list of cities passed in to the function */
double findRouteFastestCustom(std::list<QString> * orderedCities, std::list<QString> * includedCities, double distance)
{
    QSqlQuery query;
    QString start;
    unsigned long size = 0;
    //bool startFound = false;
    if(orderedCities->size() == 0)
    {   /*
        //this finds the first city with the shortest dist.
        query.exec("SELECT start, MIN(distance) From citydata");
        while(query.next() && !startFound)
        {
            if(!checkCity(query.value(0).toString(), includedCities))
            {
                startFound = true;
                start = query.value(0).toString();
            }
        }
        orderedCities->push_back(start);
        */

        // will start at the first city in includedCities
        start = includedCities->front();
        orderedCities->push_back(start);
        distance = 0;
    }
    else
    {
        start = orderedCities->back();
    }
    query.prepare("SELECT * FROM citydata WHERE start= ? ORDER by distance ASC");

    //start = orderedCities->back();
    query.addBindValue(start);
    query.exec();
    //int idStart = query.record().indexOf("start");
    int idFinish = query.record().indexOf("finish");
    int idDistance = query.record().indexOf("distance");
    QString finish;
    bool endSearch = false;

    while(!endSearch && query.next())
    {
        if(checkCity(query.value(idFinish).toString(), orderedCities) && !checkCity(query.value(idFinish).toString(), includedCities))
        {
            distance += query.value(idDistance).toDouble();
            finish = query.value(idFinish).toString();
            endSearch = true;
        }
    }
    orderedCities->push_back(finish);
    size = includedCities->size();
    if(orderedCities->size() < size)
    {
        query.finish();
        return findRouteFastestCustom(orderedCities, includedCities, distance);
    }
    else
    {
        return distance;
    }
}
