#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QListWidgetItem>
#include "trippage.h"
#include "finalpage.h"
#include "customtrippage.h"
#include "numcities.h"
#include <QTreeWidgetItem>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void resetStackW();
    void pagePrevious();
    void nextPage();
    void tripFinish();
    void Trip2(int nCities);
    void Trip3(std::list<QString> * initCities);

private slots:
    void on_Trip1_clicked();
    void on_Trip2_clicked();
    void on_Trip3_clicked();

private:
    Ui::MainWindow *ui = nullptr;
    numCities * nCityDialog = nullptr;
    customTripPage * planner = nullptr;
    tripPage ** pages = nullptr;
    finalpage * finalPage = nullptr;
    unsigned long long listSize;

};

#endif // MAINWINDOW_H
