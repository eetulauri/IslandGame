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
    gameState_(gameState),
    moveActors_(false)
{

    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene_ = scene;

    QObject::connect(ui->skipTurnButton, &QPushButton::clicked,
                     this, &MainUI::nextPhase);

    QObject::connect(ui->spinWheelButton, &QPushButton::clicked,
                     this, &MainUI::spinWheel);

    // setting button to be disabled by default and enabling it at the
    // start of SPINNING gamephase
    ui->spinWheelButton->setEnabled(false);

    // draws the board
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
    std::cout << "DEBUG: no corresponding hex found" << std::endl;
    return nullptr;
}

void MainUI::gamePhaseMovement(std::shared_ptr<Common::Hex> hex)
{
    // if its the 1st click
    if (selectedHex_ == nullptr) {
        selectedHex_ = hex;
        std::vector<std::shared_ptr<Common::Pawn> > pawns = selectedHex_->getPawns();

        // checking if the clicked tile has a pawn
        if (pawns.size() != 0) {
            std::shared_ptr<Common::Pawn> pawn = pawns.at(0);
            // checking if the clicked tiles pawn is the players own pawn
            if (pawn->getPlayerId() == gameState_->currentPlayer()) {
                pawn_ = pawns.at(0);
            } else {
                ui->textEdit->append("Incorrect tile: that is not your pawn");
                GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                graphicHex->resetClicked();
                //graphicHex = getCorrespondingGraphicHex(selectedHex_);
                //graphicHex->resetClicked();
                selectedHex_ = nullptr;
                return;
            }
        } else {
            ui->textEdit->append("Incorrect tile: no pawn there");
            GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
            graphicHex->resetClicked();
            //graphicHex = getCorrespondingGraphicHex(selectedHex_);
            //graphicHex->resetClicked();
            selectedHex_ = nullptr;
            return;
        }
    }
    // if its the 2nd click
    else {
        try {
            // moving the pawn. return value is not needed since we're only permitting moving once per turn
            gameRunner_->movePawn(selectedHex_->getCoordinates(), hex->getCoordinates(), pawn_->getId());

            for (auto &graphicalHex : graphicHexesVector_) {
                if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                    graphicalHex->resetClicked();
                }
            }

            selectedHex_ = nullptr;
            pawn_ = nullptr;

            nextPhase();


        }
        catch(Common::IllegalMoveException &i)
        {
            std::cout << i.msg() << std::endl;
            ui->textEdit->append(QString::fromStdString(i.msg()));

            // resetting all clicked hex tiles
            for (auto &graphicalHex : graphicHexesVector_) {
                if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                    graphicalHex->resetClicked();
                }
            }
            selectedHex_ = nullptr;
            pawn_ = nullptr;
        }
    }
}

void MainUI::gamePhaseSinking(std::shared_ptr<Common::Hex> hex)
{

    GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
    try {
        gameRunner_->flipTile(hex->getCoordinates());
        graphicHex->resetClicked();
        graphicHex->changeType(hex->getPieceType());
        nextPhase();
    }
    catch(Common::IllegalMoveException &i) {
        std::cout << i.msg() << std::endl;
        ui->textEdit->append(QString::fromStdString(i.msg()));
        graphicHex->resetClicked();
    }

}

void MainUI::gamePhaseSpinning(std::shared_ptr<Common::Hex> hex)
{
    // player must spin the wheel 1st before any actors can be moved
    if (moveActors_ == false) {
        printCurrentPlayerTurn();
        ui->textEdit->append("Its Game Phase Spinning! Spin the wheel!");
        GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
        graphicHex->resetClicked();
        return;
    } else {
        // the 1st click
        if (selectedHex_ == nullptr) {
            std::vector<std::shared_ptr<Common::Actor> > actors = hex->getActors();
            std::vector<std::shared_ptr<Common::Transport> > transports = hex->getTransports();

            if (actors.size() != 0) {
                std::shared_ptr<Common::Actor> actor = actors.at(0);
                if (actor->getActorType() == wheel_.first) {
                    actor_ = actors.at(0);
                    selectedHex_ = hex;
                } else {
                    ui->textEdit->append("Incorrect tile: not the correct actor");
                    GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                    graphicHex->resetClicked();
                    selectedHex_ = nullptr;
                    return;
                }

            } else if (transports.size() == 0) {
                ui->textEdit->append("Incorrect tile: no actor there");
                GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                graphicHex->resetClicked();
                selectedHex_ = nullptr;

            }

            if (transports.size() != 0) {
                std::shared_ptr<Common::Transport> transport = transports.at(0);
                if (transport->getTransportType() == wheel_.first) {
                    transport_ = transports.at(0);
                    selectedHex_ = hex;
                } else {
                    ui->textEdit->append("Incorrect tile: not the correct transport");
                    GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                    graphicHex->resetClicked();
                    selectedHex_ = nullptr;
                    return;
                }

            } else if (actors.size() == 0) {
                ui->textEdit->append("Incorrect tile: no transport there");
                GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                graphicHex->resetClicked();
                selectedHex_ = nullptr;
                return;
            }



        }
        // the second click
        else {
            try {
                if (actor_ != nullptr) {
                    gameRunner_->moveActor(selectedHex_->getCoordinates(),
                                           hex->getCoordinates(),
                                           actor_->getId(),
                                           wheel_.second);

                } else if (transport_ != nullptr) {
                    gameRunner_->moveTransportWithSpinner(selectedHex_->getCoordinates(),
                                                          hex->getCoordinates(),
                                                          transport_->getId(),
                                                          wheel_.second);
                }



                for (auto &graphicalHex : graphicHexesVector_) {
                    if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                        graphicalHex->resetClicked();
                    }
                }

                nextPhase();

            }
            catch(Common::IllegalMoveException &i) {
                std::cout << i.msg() << std::endl;
                ui->textEdit->append(QString::fromStdString(i.msg()));
                for (auto &graphicalHex : graphicHexesVector_) {
                    if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                        graphicalHex->resetClicked();
                    }
                }
                selectedHex_ = nullptr;
                pawn_ = nullptr;
            }
        }
    }
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

void MainUI::nextPhase()
{
    // checking which phase the game is on
    if (gameState_->currentGamePhase() == Common::MOVEMENT) {
        gameState_->changeGamePhase(Common::SINKING);
        ui->textEdit->append("Game Phase changed to: Sinking");
        printCurrentPlayerTurn();
        selectedHex_ = nullptr;
        pawn_ = nullptr;
    } else if (gameState_->currentGamePhase() == Common::SINKING) {
        gameState_->changeGamePhase(Common::SPINNING);
        ui->textEdit->append("Game Phase changed to: Spinning");
        printCurrentPlayerTurn();
        ui->spinWheelButton->setEnabled(true);
    }
    // if player wishes to skip spinning phase playerTurn is passed on to the next player
    // and he begins at movement phase
    else {
        gameState_->changeGamePhase(Common::MOVEMENT);
        ui->textEdit->append("Game Phase changed to: Movement");

        if(gameState_->currentPlayer() == gameRunner_->playerAmount()) {
            gameState_->changePlayerTurn(1);
        } else {
            gameState_->changePlayerTurn(gameState_->currentPlayer()+1);
        }
        printCurrentPlayerTurn();
        // we dont want previous selected hexes interfering with the next players actions
        selectedHex_ = nullptr;
        pawn_ = nullptr;
        actor_ = nullptr;
        transport_ = nullptr;
        // resetting wheel
        wheel_ = std::make_pair("","");
        moveActors_ = false;
        ui->spinWheelButton->setEnabled(false);
    }

    /*
    // if its the last players turn, gamePhase is changed to the next phase
    // otherwise the turn is given to the next player
    if(gameState_->currentPlayer() == gameRunner_->playerAmount()) {
        if (gameState_->currentGamePhase() == Common::MOVEMENT) {
            gameState_->changeGamePhase(Common::SINKING);
            ui->textEdit->append("Game Phase changed to: Sinking");
        } else if (gameState_->currentGamePhase() == Common::SINKING) {
            gameState_->changeGamePhase(Common::SPINNING);
            ui->textEdit->append("Game Phase changed to: Spinning");
        } else {
            gameState_->changeGamePhase(Common::MOVEMENT);
            ui->textEdit->append("Game Phase changed to: Movement");
        }
        gameState_->changePlayerTurn(1);
        printCurrentPlayerTurn();
        selectedHex_ = nullptr;
        pawn_ = nullptr;
    } else {
        gameState_->changePlayerTurn((gameState_->currentPlayer()+1));
        printCurrentPlayerTurn();
    }
    */
}

void MainUI::spinWheel()
{
    wheel_ = gameRunner_->spinWheel();

    QString str = QString::fromStdString(wheel_.first);
    str.append(" moves ");
    str.append(QString::fromStdString(wheel_.second));
    str.append(" steps.");
    ui->textEdit->append(str);

    // enabling moving actors after the wheel is spun
    moveActors_ = true;

}


