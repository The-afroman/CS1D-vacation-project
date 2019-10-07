#include "database.h"


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
        qDebug() << "city add error:  "
                 << query.lastError();
    }

    return success;
}

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

// finds the shortest first trip and makes that the starting city
QString findFirstCity()
{
    QSqlQuery query;
    query.exec("SELECT start, MIN(distance) FROM citydata");
    query.first();
    return query.value(0).toString();
}

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

void findRouteFastest(std::list<QString> * orderedCities, unsigned long numCities, QString startCity)
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
    //int idDistance = query.record().indexOf("distance");
    QString finish;
    bool endSearch = false;

    while(!endSearch && query.next())
    {
        if(checkCity(query.value(idFinish).toString(), orderedCities))
        {
            //qDebug() << query.value(idDistance).toDouble() << " " << query.value(idFinish).toString() << " ";
            finish = query.value(idFinish).toString();
            endSearch = true;
        }
    }
    orderedCities->push_back(finish);
    if(orderedCities->size() < numCities)
    {
        query.finish();
        findRouteFastest(orderedCities, numCities, startCity);
    }
}

void findRouteFastestCustom(std::list<QString> * orderedCities, std::list<QString> * includedCities)
{
    QSqlQuery query;
    QString start;
    unsigned long size = 0;
    bool startFound = false;
    if(orderedCities->size() == 0)
    {
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
    //int idDistance = query.record().indexOf("distance");
    QString finish;
    bool endSearch = false;

    while(!endSearch && query.next())
    {
        if(checkCity(query.value(idFinish).toString(), orderedCities) && !checkCity(query.value(idFinish).toString(), includedCities))
        {
            //qDebug() << query.value(idDistance).toDouble() << " " << query.value(idFinish).toString() << " ";
            finish = query.value(idFinish).toString();
            endSearch = true;
        }
    }
    orderedCities->push_back(finish);
    size = includedCities->size();
    if(orderedCities->size() < size)
    {
        query.finish();
        findRouteFastestCustom(orderedCities, includedCities);
    }
}
