#include "mainui.hh"
#include "ui_mainui.h"

MainUI::MainUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUI)
{

    ui->setupUi(this);
    //std::shared_ptr<QGraphicsScene> scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene());
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene_ = scene;
}

MainUI::~MainUI()
{
    delete ui;
}
