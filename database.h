#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

class DbManager
{
public:
    DbManager(const QString& path);
    bool addCity(const QString&,  const QString&, const double &);
    void printCities();
    void eraseData();
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

   //USED THIS TO CREATE THE TABLE BUT YOU ONLY NEED TO CREATE IT ONCE SOOOOOOO
 //QSqlQuery query("CREATE TABLE cities2 (id INTEGER PRIMARY KEY, start TEXT, finish TEXT, distance DOUBLE)");
 //if(!query.isActive())
 //    qWarning() << "ERROR: " << query.lastError().text();
}

bool DbManager::addCity(const QString& start, const QString& finish, const double& distance)
{
    bool success = false;
       // you should check if args are ok first...
       QSqlQuery query;
       query.prepare("INSERT INTO cities2 (start, finish, distance) VALUES (:start, :finish, :distance)");
       query.bindValue(":start", start);
       query.bindValue(":finish", finish);
       query.bindValue(":distance", distance);
       if(query.exec())
       {
           success = true;
       }
       else
       {
            qDebug() << "addPerson error:  "
                     << query.lastError();
       }

       return success;
}

void DbManager::printCities(){
    QSqlQuery query("SELECT * FROM cities2");
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

void DbManager::eraseData(){
    QSqlQuery query;
    query.prepare("DELETE FROM cities2");
    query.exec();
}

#endif // DATABASE_H
