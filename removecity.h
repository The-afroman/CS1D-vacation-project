#ifndef REMOVECITY_H
#define REMOVECITY_H
#include <QListWidgetItem>
#include <QDialog>

namespace Ui {
class removecity;
}

class removecity : public QDialog
{
    Q_OBJECT

public:
    explicit removecity(QWidget *parent = nullptr);
    ~removecity();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_listWidget_itemPressed(QListWidgetItem *item);

private:
    QString cityname;
    Ui::removecity *ui;
};

#endif // REMOVECITY_H
