#include "mainwindow.h"
#include <QApplication>
#include "login.h"
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    a.setQuitOnLastWindowClosed(false);
    login z;
    z.show();
    return a.exec();
}

