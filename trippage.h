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

class tripPage : public QWidget
{
    Q_OBJECT

public:
    explicit tripPage(QWidget *parent = nullptr);
    ~tripPage();

    void setTitle(QString &);
    QString getTitle()const;
    void setTextButtonOne(QString &);
    void setTextButtonTwo(QString &);
    void setFoodData(list<QString> *, list<double> *);
    void initFoodUI();
    QString getTextButtonTwo()const;
    int getFoodListSize()const;
    void setFoodListSize(int);
    double getTotal();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_valueChanged();

signals:

    void changePageNext();
    void changePagePrev();
    void valueChanged();
    void finishTrip();

private:
    void setFoodNameLabel(const QString &, int count);
    void appendFoodLabel(const double &, int count);
    Ui::tripPage *ui;
    QLabel * cityTitle;
    QLabel ** foodNameLabels;
    QSpinBox ** foodQtyBox;
    list<QString> *foodNames;
    list<double> *foodPrices;
    QHBoxLayout * hbox;
    QWidget * tempW;
    QLabel * priceLabel;
    QLabel * distanceSoFar;
    int sizeOfFoodLists;
    double total;

};

#endif // TRIPPAGE_H
