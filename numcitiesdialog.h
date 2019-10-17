#ifndef NUMCITIESDIALOG_H
#define NUMCITIESDIALOG_H

#include <QDialog>

namespace Ui {
class numCitiesDialog;
}

class numCitiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit numCitiesDialog(QWidget *parent = nullptr);
    ~numCitiesDialog();

private:
    Ui::numCitiesDialog *ui;
};

#endif // NUMCITIESDIALOG_H
