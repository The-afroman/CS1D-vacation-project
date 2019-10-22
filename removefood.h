#ifndef REMOVEFOOD_H
#define REMOVEFOOD_H
#include <QListWidgetItem>
#include <QDialog>

namespace Ui {
class removefood;
}

/*! Class removefood is used to remove a food item from the database by clicking
 * on the name of the food from a list widget and clicking the remove button.
 * This is only accessible to an admin user.*/
class removefood : public QDialog
{
    Q_OBJECT

public:
    explicit removefood(QWidget *parent = nullptr);

    //! destructor
    ~removefood();

private slots:
    //! called when change price button is clicked
    void on_pushButton_clicked();

    //! determines which food otem to delete
    void on_listWidget_itemClicked(QListWidgetItem *item);

    //! called when return to admin panel button is clicked
    void on_pushButton_2_pressed();

    //! called when remove food is clicked
    void on_pushButton_3_clicked();

    void on_plainTextEdit_textChanged();

private:
    Ui::removefood *ui;
    QString foodname; //!< food item to delete
};

#endif // REMOVEFOOD_H
