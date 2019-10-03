#ifndef ADDCITY_H
#define ADDCITY_H
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class addcity;
}

class addcity : public QDialog
{
    Q_OBJECT

public:
    explicit addcity(QWidget *parent = nullptr);
    ~addcity();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_textBrowser_2_textChanged();

private:
    Ui::addcity *ui;
    QString cityname;
};

#endif // ADDCITY_H
