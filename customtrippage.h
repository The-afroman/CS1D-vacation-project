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

class customTripPage : public QWidget
{
    Q_OBJECT

public:
    explicit customTripPage(QWidget *parent = nullptr);
    ~customTripPage();
    std::list<QString> * getCityList();

private slots:
    //void on_backBtn_clicked();
    void on_finishBtn_clicked();
    void on_addBtn_clicked();
    void on_removeBtn_clicked();


signals:
    void changetoPagePrev();
    void finish(std::list<QString> * initCities);
private:
    Ui::customTripPage * ui;
    std::list<QString> * cities;
};

#endif // CUSTOMTRIPPAGE_H
