#include "mainui.hh"
#include "ui_mainui.h"

MainUI::MainUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUI),
    gameBoard_(std::shared_ptr<Student::GameBoard>(new Student::GameBoard())),
    gameState_(std::shared_ptr<Student::GameState>(new Student::GameState()))
{

    ui->setupUi(this);
    //std::shared_ptr<QGraphicsScene> scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene());
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene_ = scene;
    ui->graphicsView->show();


    drawHex();
}

MainUI::~MainUI()
{
    delete ui;
}


void MainUI::drawHex()
{
    for (int i = 0; i < 10;i++)
    {
        GraphicHex *graphic_hex = new GraphicHex();
        scene_->addItem(graphic_hex);
    }

    std::vector<std::shared_ptr<Common::Hex>> hexesContainer = gameBoard_->returnHexesContainer();

    for (auto hex : hexesContainer)
    {
        // koodia
    }


}
