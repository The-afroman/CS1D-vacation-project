#ifndef SHORTESTTRIPWINDOW_H
#define SHORTESTTRIPWINDOW_H
#pragma once
#include <QDialog>
#include <QSpinBox>

namespace Ui {
class ShortestTripWindow;
}

class ShortestTripWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ShortestTripWindow(QWidget *parent = nullptr);
    ~ShortestTripWindow();

private slots:
    void on_confirmTrip_clicked();

private:

    Ui::ShortestTripWindow *ui;
};

#endif // SHORTESTTRIPWINDOW_H
