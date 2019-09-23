#ifndef SHORTESTTRIPWINDOW_H
#define SHORTESTTRIPWINDOW_H

#include <QDialog>

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
    void on_showTrip_clicked();

private:
    Ui::ShortestTripWindow *ui;
};

#endif // SHORTESTTRIPWINDOW_H
