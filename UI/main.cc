#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "igamerunner.hh"
#include "initialize.hh"
#include "mainui.hh"
#include "gameengine.hh"
#include "igameboard.hh"
#include "igamestate.hh"
#include "iplayer.hh"
#include "dialog.hh"
#include "ioexception.hh"
#include "formatexception.hh"


#include <memory>
#include <iostream>
#include <QApplication>
#include <QObject>
#include <exception>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Dialog Startingdialog;
    int playerCount = 2;

    //Setting up starting dialog and getting the player amount.
    if(Startingdialog.exec() == QDialog::Accepted)
    {
        playerCount = Startingdialog.getSpinBoxValue();
    }
    else{
        return EXIT_FAILURE;
    }

    std::shared_ptr<Student::GameBoard> gameBoard = std::make_shared<Student::GameBoard>();
    std::shared_ptr<Student::GameState> gameState = std::make_shared<Student::GameState>();

    std::vector<std::shared_ptr<Common::IPlayer>> playerVector;


    for( int a = 1; a < playerCount+1; a++){
        std::shared_ptr<Student::Player> player1 = std::make_shared<Student::Player>(a);
        playerVector.push_back(player1);
        gameBoard->addPlayer(player1);
    }

    std::shared_ptr<Common::IGameRunner> gameRunner;
    try {
        gameRunner = Common::Initialization::getGameRunner(gameBoard, gameState, playerVector);

    }
    catch(Common::IoException &i) {
        std::cout << i.msg() << std::endl;
        return EXIT_FAILURE;
    }
    catch(Common::FormatException &i) {
        std::cout << i.msg() << std::endl;
        return EXIT_FAILURE;
    }

    gameBoard->createPawns();
    MainUI w(gameBoard, gameRunner, gameState);
    w.show();



    return a.exec();
}
