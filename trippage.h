#ifndef TRIPPAGE_H
#define TRIPPAGE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <iostream>
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


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:

    void changePageNext();
    void changePagePrev();

private:
    void setFoodNameLabel(const QString &, int count);
    void appendFoodLabel(const double &, int count);
    void initFoodUI();
    Ui::tripPage *ui;
    QLabel * cityTitle;
    QLabel ** foodNameLabels;
    QSpinBox ** foodQtyBox;
    list<QString> *foodNames;
    list<double> *foodPrices;

};

#endif // TRIPPAGE_H
