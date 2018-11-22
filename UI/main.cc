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


#include <memory>
#include <iostream>
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);



    std::shared_ptr<Student::GameBoard> gameBoard = std::make_shared<Student::GameBoard>();
    std::shared_ptr<Student::GameState> gameState = std::make_shared<Student::GameState>();

    std::vector<std::shared_ptr<Common::IPlayer>> playerVector;



    for( int a = 1; a < 6; a = a + 1 ){
        std::shared_ptr<Student::Player> player1 = std::make_shared<Student::Player>(a);
        playerVector.push_back(player1);
        gameBoard->addPlayer(player1);
    }


    //std::shared_ptr<Logic::GameEngine> gameEngine
      //      = std::shared_ptr<Logic::GameEngine>(new Logic::GameEngine(gameBoard, gameState, playerVector));


    //std::shared_ptr<Common::IGameRunner> gameRunner
            //= std::shared_ptr<Logic::GameEngine>(new Common::IGameRunner(gameBoard, gameState, playerVector));
    std::shared_ptr<Common::IGameRunner> gameRunner
            = Common::Initialization::getGameRunner(gameBoard, gameState, playerVector);

    gameBoard->createPawns();
    MainUI w(gameBoard);
    //w.initializeGameRunner(gameRunner);


    w.show();


    return a.exec();
}
