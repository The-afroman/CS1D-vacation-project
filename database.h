#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <iostream>
#include <fstream>

class DbManager
{
public:
    DbManager(const QString& path);
    bool addCity(const QString&,  const QString&, const double &);
    void printCities();
    void eraseData();
    void printFoods();
private:
    QSqlDatabase m_db;
};

DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

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
            qDebug() << "add error:  "
                     << query.lastError();
       }

       return success;
}

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

void DbManager::eraseData(){
    QSqlQuery query;
    query.prepare("DELETE FROM citydata");
    query.exec();
}

void loadCityData(DbManager & db){

    std::ifstream input;
    input.open("/home/f/projects/CS1D-vacation-project/distancedata.csv");
    std::string startCity;
    std::string endCity;
    std::string distance;
    std::string dummyLine;

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
        std::cout << "Could not open data.csv" << std::endl;
    }
}
#endif // DATABASE_H
