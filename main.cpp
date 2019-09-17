#include "mainwindow.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DbManager test("/home/f/projects/CS1D-vacation-project/testdb");

    return a.exec();
}
