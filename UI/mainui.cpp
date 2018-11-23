#include "mainui.hh"
#include "ui_mainui.h"

MainUI::MainUI(std::shared_ptr<Student::GameBoard> gameBoard, std::shared_ptr<Common::IGameRunner> gameRunner,
               QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUI),
    gameBoard_(gameBoard),
    gameRunner_(gameRunner)
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

    //std::vector<std::shared_ptr<Common::Hex>> hexesContainer = gameBoard_->getHexesContainer();
    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexesMap = gameBoard_->getHexesContainer();

    int size = 28;

    for (auto element : hexesMap)
    {
        std::shared_ptr<Common::Hex> hex = element.second;
        Common::CubeCoordinate coord = hex->getCoordinates();
        QPoint axial_coord = cube_to_axial(coord);
        QPointF pixel_point = axial_to_pixel(axial_coord, size);
        GraphicHex *graphicalHex = new GraphicHex(size, hex->getPieceType(), pixel_point, element.second, element.first);
        scene_->addItem(graphicalHex);

        /*
        QObject::connect(&graphicalHex, SIGNAL(hexOnClick(std::shared_ptr<Common::Hex>)),
                         this, SLOT(givePawnNewCoordinates(std::shared_ptr<Common::Hex>)));
                         */
        QObject::connect(graphicalHex, &GraphicHex::hexOnClick,
                         this, &MainUI::givePawnNewCoordinates);


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

void MainUI::givePawnNewCoordinates(std::shared_ptr<Common::Hex> hex)
{
    try
    {
    if (selectedHex_ == nullptr) {
        selectedHex_ = hex;
        std::vector<std::shared_ptr<Common::Pawn> > pawns = selectedHex_->getPawns();
        if (pawns.size() != 0) {
            pawn_ = pawns.at(0);
        } else {
            selectedHex_ = nullptr;
        }

    } else {

        gameRunner_->movePawn(selectedHex_->getCoordinates(), hex->getCoordinates(), pawn_->getId());
        selectedHex_ = nullptr;
        pawn_ = nullptr;
        }
    }
    catch(Common::IllegalMoveException &i)
    {
        std::cout << i.msg() << std::endl;
    }


}


