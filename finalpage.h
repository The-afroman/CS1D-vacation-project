#ifndef FINALPAGE_H
#define FINALPAGE_H

#include <QDialog>
#include "database.h"
#include "trippage.h"

namespace Ui {
class finalpage;
}

class finalpage : public QDialog
{
    Q_OBJECT

public:
    explicit finalpage(QWidget *parent = nullptr);
    ~finalpage();
    void setPages(tripPage **);

private slots:
    void on_finish_clicked();

private:
    Ui::finalpage *ui;
    tripPage ** pages;
};

#endif // FINALPAGE_H
