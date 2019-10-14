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
    void addTreeItems(const QList<QTreeWidgetItem *> item);
    ~finalpage();

private:
    void initUI();
    Ui::finalpage *ui;
    vector<double> totalsList;
    int listSize;
};

#endif // FINALPAGE_H
