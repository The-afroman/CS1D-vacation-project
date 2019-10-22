#ifndef TRIPPAGE_H
#define TRIPPAGE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <QLayout>
#include <iostream>
#include <QDebug>
#include <QSlider>
using namespace std;


namespace Ui {
class tripPage;
}

/*! Class for the trip page. A trip page is a page created for every city during a trip.
Each page displays the city name and the food in each city and total cost for that city.
It also allows the user to choose the quantity of each type of food to buy.
It displays the price of each food item and total cost. The trip page can also be used to switch to a
previously visited city, to go to the next city and finish the trip.*/
class tripPage : public QWidget
{
    Q_OBJECT

public:
    explicit tripPage(QWidget *parent = nullptr);

    //! destructor
    ~tripPage();

    //! set the city title
    void setTitle(QString &);

    //! returns the city title
    QString getTitle()const;

    //! Sets the text of the first button
    void setTextButtonOne(QString &);

    //! Sets the text of the second button
    void setTextButtonTwo(QString &);

    //! sets the data of the food
    void setFoodData(list<QString> *, list<double> *);

    //! displays the formated ui for food for the trip page
    void initFoodUI();

    //! returns the text of the second button
    QString getTextButtonTwo()const;

    //! returns the size of the list of food items
    int getFoodListSize()const;

    //! sets the size of the food list
    void setFoodListSize(unsigned long long);

    //! returns the cost as a double
    double getTotal()const;

    //! returns the food qty box
    QSpinBox ** getFoodQtyBox() const;

    //! returns the names of the food
    list<QString> * getFoodNames() const;

    //! returns the prices of the food
    list<double> * getFoodPrices() const;

    //! returns the labels displaying the names of the food in ui
    QLabel ** getFoodLabels()const;


private slots:
    //! called when prev city button is clicked
    void on_pushButton_clicked();

    //! called when next city or finish trip is clicked
    void on_pushButton_2_clicked();

    void on_valueChanged();

signals:

    //! switches to the next page, the next city
    void changePageNext();

    //! switches to the previous page, the previous city
    void changePagePrev();

    void valueChanged();

    //! switches to the final page of the trip displaying final details
    void finishTrip();

private:
    //! sets the name of the food labels
    void setFoodNameLabel(const QString &, int count);

    //! Adds more to the food labels like price
    void appendFoodLabel(const double &, int count);
    Ui::tripPage *ui;
    QLabel * cityTitle; //!< label to display the name of a city
    QLabel ** foodNameLabels; //!< label to display the names of food
    QSpinBox ** foodQtyBox; //!< spin box to choose quantity of food item to purchase
    list<QString> *foodNames; //!< list of all the names of the food
    list<double> *foodPrices; //!< list of all the prices of the food
    QHBoxLayout * hbox;
    QWidget * tempW;
    QLabel * priceLabel; //!< label to display price of each food
    QLabel * distanceSoFar;
    unsigned long long sizeOfFoodLists;
    double total = 0;

};

#endif // TRIPPAGE_H
