#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "graphichex.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setScene();

};

#endif // MAINWINDOW_HH
