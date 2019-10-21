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

/*! Class for the main window of the program.
 * Allows the user to see the name of the project,
 * the available cities to travel to. Also allows the
 * user to switch user and click on the three trip option.*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    //! destructor
    ~MainWindow();

public slots:
    //! resets stack widget so it can be used again if a new trip is started
    void resetStackW();

    //! called to go to previous city page in trip
    void pagePrevious();

    //! called to go to next city page in trip
    void nextPage();

    //! called to finish the current trip
    void tripFinish();

    //! creates the second trip
    void Trip2(int nCities);

    //! creates the third trip
    void Trip3(std::list<QString> * initCities);

private slots:
    //! called when basic trip is clicked
    void on_Trip1_clicked();

    //! called when fastest trip is clicked
    void on_Trip2_clicked();

    //! called when custom trip is clicked
    void on_Trip3_clicked();

    //! opens login window
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui = nullptr;
    numCities * nCityDialog = nullptr; //!< numCities object
    customTripPage * planner = nullptr; //!< customTripPage object
    tripPage ** pages = nullptr; //!< trip page object
    finalpage * finalPage = nullptr; //!< final page object
    unsigned long long listSize;

};

#endif // MAINWINDOW_H
