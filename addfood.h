#ifndef ADDFOOD_H
#define ADDFOOD_H
#include <QListWidgetItem>
#include <QDialog>

namespace Ui {
class addfood;
}

/*! Class addfood is so the admin can add more food items to
 * the cities in the database as well as the prices for the food added*/
class addfood : public QDialog
{
    Q_OBJECT

public:
    explicit addfood(QWidget *parent = nullptr);

    //! destructor
    ~addfood();

private slots:

    //! called when return to admin screen button is pressed
    void on_pushButton_2_clicked();

    //! called when add food button is clicked
    void on_pushButton_clicked();

    //! determines the name of the city to add food
    void on_listWidget_itemClicked(QListWidgetItem *item);


private:
    QString cityname;
    Ui::addfood *ui;
};

#endif // ADDFOOD_H
