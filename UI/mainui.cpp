#include "mainui.hh"
#include "ui_mainui.h"

MainUI::MainUI(std::shared_ptr<Student::GameBoard> gameBoard,
               QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUI),
    gameBoard_(gameBoard)
    //gameState_(gameState)
{

    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene_ = scene;

    drawHex();
}

MainUI::~MainUI()
{
    delete ui;
}


void MainUI::drawHex()
{

    std::vector<std::shared_ptr<Common::Hex>> hexesContainer = gameBoard_->getHexesContainer();

    int size = 28;

    for (auto hex : hexesContainer)
    {
        Common::CubeCoordinate coord = hex->getCoordinates();
        QPoint axial_coord = cube_to_axial(coord);
        GraphicHex *graphicalHex = new GraphicHex(size, hex->getPieceType());
        QPointF pixel_point = axial_to_pixel(axial_coord, size);
        scene_->addItem(graphicalHex);
        graphicalHex->setPos(pixel_point);
    }

}

QPoint MainUI::cube_to_axial(Common::CubeCoordinate coord)
{
    int q = coord.x;
    int r = coord.z;
    return QPoint(q, r);
}

QPointF MainUI::axial_to_pixel(QPoint point, int size)
{
    double x = size * (sqrt(3) * point.x() + sqrt(3)/2 * point.y());
    double y = size * (3./2 * point.y());
    return QPointF(x, y);
}
