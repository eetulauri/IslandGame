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
    //std::shared_ptr<QGraphicsScene> scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene());
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
    /*
    for (int i = 0; i < 10;i++)
    {
        GraphicHex *graphic_hex = new GraphicHex();
        scene_->addItem(graphic_hex);
    }
    */


    std::vector<std::shared_ptr<Common::Hex>> hexesContainer = gameBoard_->getHexesContainer();

    //std::map<QPoint, std::string> points;

    int size = 25;

    for (auto hex : hexesContainer)
    {
        Common::CubeCoordinate coord = hex->getCoordinates();
        QPoint axial_coord = cube_to_axial(coord);
        //points.push_back(axial_coord);
        //points[axial_coord] = hex->getPieceType();
        GraphicHex *graphicalHex = new GraphicHex(size, hex->getPieceType());
        QPoint pixel_point = axial_to_pixel(axial_coord, size);
        scene_->addItem(graphicalHex);
        graphicalHex->setPos(pixel_point);

    }


    /*
    for (std::map<QPoint, std::string>::const_iterator it=points.begin(); it!=points.end(); ++it)
    {

        GraphicHex *graphicalHex = new GraphicHex(size, it->second);
        QPoint pixel_point = axial_to_pixel(it->first, size);
        scene_->addItem(graphicalHex);
        graphicalHex->setPos(pixel_point);
    }
    */



}

QPoint MainUI::cube_to_axial(Common::CubeCoordinate coord)
{
    int q = coord.x;
    int r = coord.z;
    return QPoint(q, r);
}

QPoint MainUI::axial_to_pixel(QPoint point, int size)
{
    float x = size * (sqrt(3) * point.x() + sqrt(3)/2 * point.y());
    float y = size * (3./2 * point.y());
    return QPoint(x, y);
}
