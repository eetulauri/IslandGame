
#include "mainwindow.hh"

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent)
  //gameRunner_(gameRunner),
  //view_(view),
  //scene_(scene)


{


    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene);
    //view->show();
    //setScene();

}


MainWindow::~MainWindow()
{
}

void MainWindow::initializeGameRunner(std::shared_ptr<Common::IGameRunner> gameRunner)
{
    gameRunner_ = gameRunner;
}

void MainWindow::setScene()
{
    QGraphicsScene *scene = new QGraphicsScene();
    GraphicHex *hex = new GraphicHex();
    scene->addItem(hex);
    QGraphicsView *view = new QGraphicsView(scene);
    view->show();
}


