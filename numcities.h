#ifndef NUMCITIES_H
#define NUMCITIES_H

#include <QWidget>

namespace Ui {
class numCities;
}

class numCities : public QWidget
{
    Q_OBJECT

public:
    explicit numCities(QWidget *parent = nullptr, int maxSpinBox=11);
    ~numCities();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

signals:
    void finish(int nCities);

private:
    Ui::numCities *ui;
    int cities;
};

#endif // NUMCITIES_H
