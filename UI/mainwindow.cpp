
#include "mainwindow.hh"

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent)
{
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


