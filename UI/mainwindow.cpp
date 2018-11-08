
#include "mainwindow.hh"

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent)
{


    //QGraphicsScene *scene = new QGraphicsScene();
    //QGraphicsView *view = new QGraphicsView(scene);
    //view->show();
    setScene();
}


MainWindow::~MainWindow()
{
}

void MainWindow::setScene()
{
    QGraphicsScene *scene = new QGraphicsScene();
    GraphicHex *hex = new GraphicHex();
    scene->addItem(hex);
    QGraphicsView *view = new QGraphicsView(scene);
    view->show();
}


