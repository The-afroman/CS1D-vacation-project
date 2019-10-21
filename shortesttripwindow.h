#ifndef SHORTESTTRIPWINDOW_H
#define SHORTESTTRIPWINDOW_H

#include <QDialog>

namespace Ui {
class ShortestTripWindow;
}

/*! Class to find the shortest trip from the list of cities*/
class ShortestTripWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ShortestTripWindow(QWidget *parent = nullptr);

    //! destructor
    ~ShortestTripWindow();

private slots:
    //! finds the fastest trip
    void on_confirmTrip_clicked();

private:
    Ui::ShortestTripWindow *ui;
};

#endif // SHORTESTTRIPWINDOW_H
