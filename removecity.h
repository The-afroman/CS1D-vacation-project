#ifndef REMOVECITY_H
#define REMOVECITY_H
#include <QListWidgetItem>
#include <QDialog>

namespace Ui {
class removecity;
}

/*! Class removecity is used to remove a city from the database by clicking
 * on the name of the city from a list widget and clicking the remove button.
 * This is only accessible to an admin user.*/
class removecity : public QDialog
{
    Q_OBJECT

public:
    explicit removecity(QWidget *parent = nullptr);

    //! destructor
    ~removecity();

private slots:

    //! called when return to admin panel is pressed
    void on_pushButton_2_clicked();

    //! called when remove city is clicked
    void on_pushButton_clicked();

    //! determines which city to delete
    void on_listWidget_itemPressed(QListWidgetItem *item);

private:
    QString cityname; //!< name of city to delete
    Ui::removecity *ui;
};

#endif // REMOVECITY_H
