#ifndef FINALPAGE_H
#define FINALPAGE_H

#include <QWidget>
#include "trippage.h"
#include <QTreeWidgetItem>

namespace Ui {
class finalpage;
}

/*! Class for the implementation of the final page
 * after every trip. Shows a list of items from each city,
 * how many of each food item was bought and the subtotal
 * from each city. Also shows total distance traveled and the total cost. */
class finalpage : public QWidget
{
    Q_OBJECT

public:
    explicit finalpage(QWidget *parent = nullptr);

    //! adds items to tree widget and displays it
    void addTreeItem(const tripPage & page);

    //! destructor
    ~finalpage();

    //! used to set the total cost value
    void setNetTotal(double value);

    //! used to set the distance traveled value
    void setDistance(double distance);

signals:
    //! used to return back to main menu after trip is completed
    void backToMenu();

private slots:

    //! called when return to main menu button clicked
    void on_pushButton_clicked();

private:
    void initUI();
    Ui::finalpage *ui;
    vector<double> totalsList;
    int listSize;
    double net; //!< value for the total cost
    double distance; //!< value for the distance traveled
};

#endif // FINALPAGE_H
