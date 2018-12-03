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

    // giving players their starting coordinates so that their pawns can be
    // reset back to that position
    std::vector<Common::CubeCoordinate> coords = gameBoard->calculateCornerPieces();
    int i = 0;
    for (auto player : gameBoard_->getPlayerVector()) {
        player->setStartingCoordinates(coords.at(i));
        i++;
    }


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
                         this, &MainUI::hexClicked);


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
            }
            // if clicked pawn is no the players own pawn
            else {
                ui->textEdit->append("Incorrect tile: that is not your pawn");
                GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                graphicHex->resetClicked();
                selectedHex_ = nullptr;
                return;
            }
        }
        // if clicked hex does not have a pawn at all
        else {
            ui->textEdit->append("Incorrect tile: no pawn there");
            GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
            graphicHex->resetClicked();
            selectedHex_ = nullptr;
            return;
        }
    }
    // if its the 2nd click
    else {
        try {
            //checking that the player is not trying to move to a hex with a shark
            // or a seamunster
            std::vector<std::shared_ptr<Common::Actor> > actors = hex->getActors();
            if (actors.size() != 0) {
                std::shared_ptr<Common::Actor> actor = actors.at(0);

                if (actor->getActorType() == "shark" or actor->getActorType() == "seamunster") {
                    ui->textEdit->append("You most certainly don't want to move there...");
                    // resetting clicked tiles
                    for (auto &graphicalHex : graphicHexesVector_) {
                        if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                            graphicalHex->resetClicked();
                        }
                    }
                    // variables are reset and this method is stopped
                    selectedHex_ = nullptr;
                    pawn_ = nullptr;
                    return;
                }
            }
            // transports in 1st clicked hex
            std::vector<std::shared_ptr<Common::Transport> > transports = selectedHex_->getTransports();
            bool isPawnInTransport = false;
            std::shared_ptr<Common::Transport> transport;

            // if 1st clicked hex has transport
            if (transports.size() != 0) {
                transport = transports.at(0);
                isPawnInTransport = transport->isPawnInTransport(pawn_);
            }
            // if pawn has been set into transport in the previous turn
            if (isPawnInTransport == true) {
                // if the target hex has a pawn
                if (hex->getPawnAmount() != 0) {
                    // getting the target hex pawn
                    std::vector<std::shared_ptr<Common::Pawn> > pawns = hex->getPawns();
                    int pawnId = pawns.at(0)->getPlayerId();
                    // pawn in target hex is removed and respawned
                    hex->clearPawnsFromTerrain();
                    spawnNewPawn(pawnId);
                    // if you just double clicked the hex and ate your own pawn
                    if (selectedHex_->getCoordinates() == hex->getCoordinates()) {
                        ui->textEdit->append("whoopsie daisy, you just ate yourself! Better luck next time =)");
                    }
                    // adding a pawn kill for the player who killed the pawn
                    int playerId = gameState_->currentPlayer();
                    for (auto player : gameBoard_->getPlayerVector()) {
                        if (player->getPlayerId() == playerId) {
                            std::shared_ptr<Student::Player> playerShared = player;
                            playerShared->addToPawnKills();
                            break;
                        }
                    }
                }
                // transports can only move on water
                if (hex->getPieceType() == "Water") {
                    // moving the pawn and removing pawn from transport
                    transport->move(hex);
                    transport->removePawns();
                    ui->textEdit->append("Pawn was removed from transport!");
                } else {
                    // resetting all clicked hex tiles
                    for (auto &graphicalHex : graphicHexesVector_) {
                        if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                            graphicalHex->resetClicked();
                        }
                    }
                    ui->textEdit->append("Silly you, this transport can't move on land.");
                    selectedHex_ = nullptr;
                    pawn_ = nullptr;
                    return;
                }

            }
            else {
                // if target hex already has a pawn it is killed and respawned
                if (hex->getPawnAmount() != 0) {
                    std::vector<std::shared_ptr<Common::Pawn> > pawns = hex->getPawns();
                    int pawnId = pawns.at(0)->getPlayerId();
                    hex->clearPawnsFromTerrain();
                    spawnNewPawn(pawnId);
                    // if you ate your own pawn by double clicking
                    if (selectedHex_->getCoordinates() == hex->getCoordinates()) {
                        ui->textEdit->append("whoopsie daisy, you just ate yourself! Better luck next time =)");
                    }
                    // adding a pawnkill for the player
                    int playerId = gameState_->currentPlayer();
                    for (auto player : gameBoard_->getPlayerVector()) {
                        if (player->getPlayerId() == playerId) {
                            std::shared_ptr<Student::Player> playerShared = player;
                            playerShared->addToPawnKills();
                            break;
                        }
                    }
                }
                // moving the pawn. return value is not needed since we're only permitting moving once per turn
                gameRunner_->movePawn(selectedHex_->getCoordinates(), hex->getCoordinates(), pawn_->getId());
                std::vector<std::shared_ptr<Common::Transport> > transports1 = hex->getTransports();
                // if target hex has a transport the pawn is added to it
                if (transports1.size() != 0) {
                    std::shared_ptr<Common::Transport> transport1 = transports1.at(0);
                    transport1->addPawn(pawn_);
                    ui->textEdit->append("Pawn was added to transport!");
                }
            }
            // move counter is updated for the current player
            int playerId = gameState_->currentPlayer();
            for (auto player : gameBoard_->getPlayerVector()) {
                if (player->getPlayerId() == playerId) {
                    std::shared_ptr<Student::Player> playerShared = player;
                    playerShared->addToMovesUsed();
                    break;
                }
            }
            // checking if the player has moved to the center and has won the game
            checkIfPlayerHasWon(hex);

            // clicked hexes are reset
            for (auto &graphicalHex : graphicHexesVector_) {
                if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                    graphicalHex->resetClicked();
                }
            }
            // resetting selectedHex_ for later use
            selectedHex_ = nullptr;

            nextPhase();

        }
        // if the player is trying to do an illegal move an expection is thrown and catched here
        catch(Common::IllegalMoveException &i)
        {
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
    // getting the corresponding graphicalHex
    GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
    try {
        // flipping the clicked tile
        std::string actorName = gameRunner_->flipTile(hex->getCoordinates());

        // message for textEdit box
        QString actorSpawnMessage = "Flipped tile! ";
        actorSpawnMessage.append(QString::fromStdString(actorName));
        actorSpawnMessage.append(" spawned!");
        ui->textEdit->append(actorSpawnMessage);

        // getting the actors at the tile
        std::vector<std::shared_ptr<Common::Actor> > actorVector = hex->getActors();
        // if there is an actor
        if (actorVector.size() != 0) {
            std::shared_ptr<Common::Actor> actor = actorVector.at(0);
            std::shared_ptr<Common::Pawn> pawn = nullptr;
            // getting the current pawn
            for (auto &element : gameBoard_->getPawnMap()) {
                if (element.first == gameState_->currentPlayer()) {
                    pawn = element.second;
                    break;
                }
            }
            if (actorName == "shark" or actorName == "seamunster") {
                actor->doAction();

                if (pawn->getCoordinates() == hex->getCoordinates()) {
                    // pawn was removed and needs to be respanwed
                    spawnNewPawn(gameState_->currentPlayer());
                }

            } else if (actorName == "vortex") {
                actor->doAction();
                // if pawn is removed its respawned back to starting coordinates
                for (auto coord : hex->getNeighbourVector()) {
                    if (pawn->getCoordinates() == coord) {
                        spawnNewPawn(gameState_->currentPlayer());
                    }
                }
                if (pawn->getCoordinates() == hex->getCoordinates()) {
                    spawnNewPawn(gameState_->currentPlayer());
                }
            }

        }
        // resetting click
        graphicHex->resetClicked();
        // graphicHex is given new type
        graphicHex->changeType(hex->getPieceType());
        nextPhase();
    }
    // if an expection is thrown (clicking on tile which cannot be flipped/sunk)
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
            // getting actors and transports in hex
            std::vector<std::shared_ptr<Common::Actor> > actors = hex->getActors();
            std::vector<std::shared_ptr<Common::Transport> > transports = hex->getTransports();

            // if there are actors
            if (actors.size() != 0) {
                std::shared_ptr<Common::Actor> actor = actors.at(0);
                if (actor->getActorType() == wheel_.first) {
                    // saved for the 2nd click
                    actor_ = actors.at(0);
                    selectedHex_ = hex;
                } else {
                    // if the wrong type of actor is clicked
                    ui->textEdit->append("Incorrect tile: not the correct actor");
                    // resetting
                    GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                    graphicHex->resetClicked();
                    selectedHex_ = nullptr;
                    return;
                }
            // if clicked tile has no transports
            } else if (transports.size() == 0) {
                ui->textEdit->append("Incorrect tile: no actor there");
                GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                graphicHex->resetClicked();
                selectedHex_ = nullptr;

            }
            // if there are transports
            if (transports.size() != 0) {
                std::shared_ptr<Common::Transport> transport = transports.at(0);
                if (transport->getTransportType() == wheel_.first) {
                    transport_ = transports.at(0);
                    selectedHex_ = hex;
                } else {
                    // if its not the correct transport which is clicked
                    ui->textEdit->append("Incorrect tile: not the correct transport");
                    GraphicHex *graphicHex = getCorrespondingGraphicHex(hex);
                    graphicHex->resetClicked();
                    selectedHex_ = nullptr;
                    return;
                }

            } else if (actors.size() == 0) {
                // if there are no ransports in the clicked tile
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
                    // if the actor is shark or seamunster the pawn at target hex will be eaten
                    if (actor_->getActorType() == "shark" or actor_->getActorType() == "seamunster") {
                        actor_->doAction();
                        if (hex->getPawnAmount() != 0) {
                            std::shared_ptr<Common::Pawn> pawn = hex->getPawns().at(0);
                            spawnNewPawn(pawn->getPlayerId());
                            hex->removePawn(pawn);
                        }
                    }
                    // moving the actor
                    gameRunner_->moveActor(selectedHex_->getCoordinates(),
                                           hex->getCoordinates(),
                                           actor_->getId(),
                                           wheel_.second);
                    // kraken destroyes transports
                    if (actor_->getActorType() == "kraken") {
                        actor_->doAction();
                        ui->textEdit->append("Transport destroyed!");

                    }

                }
                // moving the transport using the moveTransportWithSpinner
                else if (transport_ != nullptr) {
                    gameRunner_->moveTransportWithSpinner(selectedHex_->getCoordinates(),
                                                          hex->getCoordinates(),
                                                          transport_->getId(),
                                                          wheel_.second);
                }
                // resetting clicked hexes
                for (auto &graphicalHex : graphicHexesVector_) {
                    if (graphicalHex->getHex() == selectedHex_ or graphicalHex->getHex()== hex) {
                        graphicalHex->resetClicked();
                    }
                }

                nextPhase();

            }
            // if player tries to do an illegal move
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
    ui->textEdit->setTextColor(Qt::red);
    QString str = "Player ";
    str.append(QString::number(gameState_->currentPlayer()));
    str.append("'s turn");
    ui->textEdit->append(str);
    ui->textEdit->setTextColor(Qt::black);
}

void MainUI::checkIfPlayerHasWon(std::shared_ptr<Common::Hex> hex)
{
    // if pawn was moved to center hex
    if (hex->getCoordinates() == Common::CubeCoordinate(0, 0, 0)) {

        QString hasWonMessage = "Player ";
        hasWonMessage.append(QString::number(gameState_->currentPlayer()));
        hasWonMessage.append(" has won the game!!! It took just ");

        int movesUsed = 0;
        int pawnKills = 0;
        int playerId = gameState_->currentPlayer();
        for (auto player : gameBoard_->getPlayerVector()) {
            if (player->getPlayerId() == playerId) {
                std::shared_ptr<Student::Player> playerShared = player;
                 movesUsed = playerShared->getMovesUsed();
                 pawnKills = playerShared->getPawnKills();
                break;
            }
        }
        hasWonMessage.append(QString::number(movesUsed));
        hasWonMessage.append(" moves!");
        hasWonMessage.append(" Pawns killed: ");
        hasWonMessage.append(QString::number(pawnKills));
        // a message box is displayed and the program exits after
        QMessageBox::information(this, "Winner winner chicken dinner", hasWonMessage);
        exit(0);

    }
}

void MainUI::spawnNewPawn(int playerId)
{
    Common::CubeCoordinate coord;
    for (auto player : gameBoard_->getPlayerVector()) {
        if (player->getPlayerId() == playerId) {
            coord = player->getStartingCoordinates();
        }
    }
    gameBoard_->addPawn(playerId, playerId, coord);
    GraphicHex *graphicalHex = getCorrespondingGraphicHex(gameBoard_->getHex(coord));
    graphicalHex->update();
    ui->textEdit->append("Truly unfortunate. A pawn has fallen in battle "
                         "but the war has not yet been lost! "
                         "A new recruit has arrived to base, make good use of him.");

}


void MainUI::hexClicked(std::shared_ptr<Common::Hex> hex)
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
        for (auto &player : gameBoard_->getPlayerVector()) {
            player->setActionsLeft(3);
        }
    }

}

void MainUI::spinWheel()
{

    std::unordered_map<std::string, std::string> imageMap = {{"dolphin", ":/images/dolphin.png"},
                                                        {"shark", ":/images/shark.png"},
                                                        {"kraken", ":/images/kraken.png"},
                                                        {"seamunster", ":/images/seamunster.png"}};


    std::vector<std::string> imageVector;

    for (auto &type :imageMap){
        imageVector.push_back(type.second);
    }

    wheel_ = gameRunner_->spinWheel();


    QString str = QString::fromStdString(wheel_.first);
    str.append(" moves ");
    str.append(QString::fromStdString(wheel_.second));
    str.append(" steps.");
    QString imgAdress;
    QString imageUrl;
    QPixmap pix;
    QFont f("Arial",200);
    ui->numLabel->setFont(f);


    for (int a = 1; a< 15; a= a+1){
        int randomNum = rand() % 4;

        imageUrl = QString::fromStdString(imageVector.at(randomNum));
        pix.load(imageUrl);
        pix = pix.scaledToWidth(220);

        randomNum += 1;
        if (randomNum == 4){
            ui->numLabel->setText("D");
        }else{
            ui->numLabel->setText(QString::number(randomNum));
        }
        ui->pictureLabel->setPixmap(pix);
        repaint();
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }

    for (auto &type : imageMap)
    {
        if(wheel_.first == type.first){

            imgAdress = QString::fromStdString(type.second);
        }
    }
    pix.load(imgAdress);
    pix = pix.scaledToWidth(220);
    ui->pictureLabel->setPixmap(pix);
    ui->textEdit->append(str);
    ui->numLabel->setText(QString::fromStdString(wheel_.second));

    // enabling moving actors after the wheel is spun
    moveActors_ = true;

}

void MainUI::wheelEvent(QWheelEvent *event)
{
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        ui->graphicsView-> scale(scaleFactor, scaleFactor);

    } else {
        // Zooming out
         ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

}

