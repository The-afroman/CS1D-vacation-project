#ifndef CUSTOMTRIPPAGE_H
#define CUSTOMTRIPPAGE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <iostream>
#include <QDebug>

namespace Ui {
class customTripPage;
}

/*! Class for the creation of a custom trip, allows
 * the user to add or remove a city from their trip
 * plan and buy food items from each city. */
class customTripPage : public QWidget
{
    Q_OBJECT

public:
    explicit customTripPage(QWidget *parent = nullptr);

    //! destructor
    ~customTripPage();

    //! returns the list of cities
    std::list<QString> * getCityList();

private slots:
    //void on_backBtn_clicked();

    //! is called when the finish trip button is clicked
    void on_finishBtn_clicked();

    //! is called when the add city button is clicked
    void on_addBtn_clicked();

    //! is called when the remove city button is clicked
    void on_removeBtn_clicked();


signals:
    //! function to go back to the previous page
    void changetoPagePrev();

    //! function to finish the trip
    void finish(std::list<QString> * initCities);
private:
    Ui::customTripPage * ui;
    std::list<QString> * cities;
};

#endif // CUSTOMTRIPPAGE_H
