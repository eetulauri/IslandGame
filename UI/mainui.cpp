#include "mainui.hh"
#include "ui_mainui.h"

MainUI::MainUI(std::shared_ptr<Student::GameBoard> gameBoard,
               std::shared_ptr<Common::IGameRunner> gameRunner,
               std::shared_ptr<Student::GameState> gameState,
               QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUI),
    gameBoard_(gameBoard),
    gameRunner_(gameRunner),
    gameState_(gameState)
{

    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene_ = scene;


    drawHex();
    ui->textEdit->append("Game Start!");
    printCurrentPlayerTurn();
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
        graphicHexesVector_.push_back(graphicalHex);

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

GraphicHex* MainUI::getCorrespondingGraphicHex(std::shared_ptr<Common::Hex> hex)
{
    for (auto graphicalHex : graphicHexesVector_) {
        if (graphicalHex->getHex() == hex) {
            return graphicalHex;
        }
    }
}

void MainUI::gamePhaseMovement(std::shared_ptr<Common::Hex> hex)
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
                ui->textEdit->append("Incorrect tile: no pawn there");
                GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                graphicHex->resetClicked();
                return;
            }
        } else {

            int movesLeft = gameRunner_->movePawn(selectedHex_->getCoordinates(), hex->getCoordinates(), pawn_->getId());
            for (auto &graphicalHex : graphicHexesVector_) {
                if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                    graphicalHex->resetClicked();
                }
            }
            selectedHex_ = nullptr;
            pawn_ = nullptr;

            ui->textEdit->append(QString::number(movesLeft));

            if (movesLeft <= 0) {
                if (gameState_->currentPlayer() == gameRunner_->playerAmount()) {
                    gameState_->changeGamePhase(Common::SINKING);
                    ui->textEdit->append("Game Phase changed to: Sinking");
                    gameState_->changePlayerTurn(1);
                    printCurrentPlayerTurn();
                } else {
                    gameState_->changePlayerTurn((gameState_->currentPlayer()+1));
                    printCurrentPlayerTurn();
                }
            }
        }
    }
    catch(Common::IllegalMoveException &i)
    {
        std::cout << i.msg() << std::endl;
        ui->textEdit->append(QString::fromStdString(i.msg()));
        GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
        graphicHex->resetClicked();
    }

}

void MainUI::gamePhaseSinking(std::shared_ptr<Common::Hex> hex)
{

    GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
    try {
        gameRunner_->flipTile(hex->getCoordinates());
        graphicHex->resetClicked();
        graphicHex->changeType(hex->getPieceType());

        if(gameState_->currentPlayer() == gameRunner_->playerAmount()) {
            gameState_->changeGamePhase(Common::SPINNING);
            ui->textEdit->append("Game Phase changed to: Spinning");
            gameState_->changePlayerTurn(1);
            printCurrentPlayerTurn();
        } else {
            gameState_->changePlayerTurn((gameState_->currentPlayer()+1));
            printCurrentPlayerTurn();
        }

    }
    catch(Common::IllegalMoveException &i) {
        std::cout << i.msg() << std::endl;
        ui->textEdit->append(QString::fromStdString(i.msg()));
        graphicHex->resetClicked();
    }

}

void MainUI::gamePhaseSpinning(std::shared_ptr<Common::Hex> hex)
{
    gameState_->changeGamePhase(Common::MOVEMENT);
    gameState_->changePlayerTurn(1);
    ui->textEdit->append("Game Phase changed to: Movement");
    printCurrentPlayerTurn();
    selectedHex_ = nullptr;
    pawn_ = nullptr;
}

void MainUI::printCurrentPlayerTurn()
{
    QString str = "Player ";
    str.append(QString::number(gameState_->currentPlayer()));
    str.append("'s turn");
    ui->textEdit->append(str);
}

void MainUI::givePawnNewCoordinates(std::shared_ptr<Common::Hex> hex)
{
    if (gameState_->currentGamePhase() == Common::MOVEMENT)
    {
        gamePhaseMovement(hex);
    }
    else if (gameState_->currentGamePhase() == Common::SINKING)
    {
        gamePhaseSinking(hex);
    }
    else if (gameState_->currentGamePhase() == Common::SPINNING) {
        gamePhaseSpinning(hex);
    }

}


