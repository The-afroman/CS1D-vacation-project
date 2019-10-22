#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

/*! Class used so the user can login*/
class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);

    //! destructor
    ~login();

private slots:

    //! takes input from login
    void on_pushButton_login_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
