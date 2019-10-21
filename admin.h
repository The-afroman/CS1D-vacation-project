#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class admin;
}

/*! Class admin is used so that when an admin logs in they can alter tha data.
 They can add food items, new cities and edit existing food items and cities*/
class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);

    //! destructor
    ~admin();

private slots:

    //! called when return to main menu button is clicked
    void on_pushButton_clicked();

    //! called when add city button is clicked
    void on_pushButton_2_clicked();

    //! called when remove city button is clicked
    void on_pushButton_4_clicked();

    //! called when add food button is clicked
    void on_pushButton_3_clicked();

    //! called when remove food button is clicked
    void on_pushButton_5_clicked();

private:
    QFileDialog *file;
    Ui::admin *ui;
};

#endif // ADMIN_H
