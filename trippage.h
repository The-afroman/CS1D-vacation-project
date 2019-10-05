#ifndef TRIPPAGE_H
#define TRIPPAGE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
using namespace std;


namespace Ui {
class tripPage;
}

class tripPage : public QWidget
{
    Q_OBJECT

public:
    explicit tripPage(QWidget *parent = nullptr);
    ~tripPage();

    void setTitle(QString &);
    const QString & getTitle();
    void setTextButtonOne(QString &);
    void setTextButtonTwo(QString &);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:

    void changePageNext();
    void changePagePrev();

private:
    Ui::tripPage *ui;
    list<QString> foodNames;
    QLabel * cityTitle;

};

#endif // TRIPPAGE_H
