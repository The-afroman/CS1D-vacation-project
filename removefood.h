#ifndef REMOVEFOOD_H
#define REMOVEFOOD_H
#include <QListWidgetItem>
#include <QDialog>

namespace Ui {
class removefood;
}

class removefood : public QDialog
{
    Q_OBJECT

public:
    explicit removefood(QWidget *parent = nullptr);
    ~removefood();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_pressed();

private:
    Ui::removefood *ui;
    QString foodname;
};

#endif // REMOVEFOOD_H
