#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QListWidgetItem>
#include "trippage.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void pagePrevious();
    void nextPage();

private slots:

    void on_Trip1_clicked();
    void on_Trip2_clicked();
    void on_Trip3_clicked();

private:
    Ui::MainWindow *ui;
    tripPage **pages;

};

#endif // MAINWINDOW_H
