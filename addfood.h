#ifndef ADDFOOD_H
#define ADDFOOD_H
#include <QListWidgetItem>
#include <QDialog>

namespace Ui {
class addfood;
}

class addfood : public QDialog
{
    Q_OBJECT

public:
    explicit addfood(QWidget *parent = nullptr);
    ~addfood();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);


private:
    QString cityname;
    Ui::addfood *ui;
};

#endif // ADDFOOD_H
