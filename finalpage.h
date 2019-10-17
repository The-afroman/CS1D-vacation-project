#ifndef FINALPAGE_H
#define FINALPAGE_H

#include <QWidget>
#include "trippage.h"
#include <QTreeWidgetItem>

namespace Ui {
class finalpage;
}

class finalpage : public QWidget
{
    Q_OBJECT

public:
    explicit finalpage(QWidget *parent = nullptr);
    void addTreeItem(const tripPage & page);
    ~finalpage();
    void setNetTotal(double value);

signals:
    void backToMenu();

private slots:
    void on_pushButton_clicked();

private:
    void initUI();
    Ui::finalpage *ui;
    vector<double> totalsList;
    int listSize;
    double net;
};

#endif // FINALPAGE_H
