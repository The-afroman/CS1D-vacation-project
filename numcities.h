#ifndef NUMCITIES_H
#define NUMCITIES_H

#include <QWidget>

namespace Ui {
class numCities;
}

/*! Class numCities is used for trip 2. A spin box will pop up so the number of cities for the trip can be chosen*/
class numCities : public QWidget
{
    Q_OBJECT

public:
    explicit numCities(QWidget *parent = nullptr);

    //! destructor
    ~numCities();

private slots:
    //! called when the button to finish choosing cities is clicked
    void on_pushButton_clicked();

    //! changes value of cities
    void on_spinBox_valueChanged(int arg1);

signals:
    void finish(int nCities);

private:
    Ui::numCities *ui;
    int cities; //! < number of cities
};

#endif // NUMCITIES_H
