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


    std::vector<std::shared_ptr<Common::Hex>> hexesContainer = gameBoard_->returnHexesContainer();

    std::vector<QPoint> points;

    for (auto hex : hexesContainer)
    {
        Common::CubeCoordinate coord = hex->getCoordinates();
        QPoint axial_coord = cube_to_axial(coord);

        points.push_back(axial_coord);
        // koodia
    }

    QPolygonF hex_points;

    double angle_deg;
    double angle_rad;
    int size = 25;

    for (int i = 0; i < 6; i++)
    {
        angle_deg = 60 * i - 30;
        angle_rad = PI / 180 * angle_deg;
        hex_points << QPoint(size * cos(angle_rad),
                             size * sin(angle_rad));
    }



    for (auto point : points)
    {


        QPen pen(Qt::black, 1);
        QBrush brush;
        QGraphicsItem *graphicalHex = scene_->addPolygon(hex_points, pen, brush);
        QPoint pixel_point = axial_to_pixel(point, size);
        graphicalHex->setPos(pixel_point);
    }





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
