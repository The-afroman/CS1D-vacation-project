#ifndef TRIPPAGE_H
#define TRIPPAGE_H

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <list>
#include "database.h"


    class tripPage : public QWidget
    {
        Q_OBJECT

    public:

        tripPage( QWidget *parent = 0);
        ~tripPage();



    private:

        void initUI();

        list<double> *prices;
        list<QString> *foods;
        list<QString> *cityNames;

        QPushButton *back;
        QPushButton *next;

    };


#endif // TRIPPAGE_H

