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

    /*
    std::shared_ptr<Student::GameBoard> gameBoard
            = std::shared_ptr<Student::GameBoard>(new Student::GameBoard());
    std::shared_ptr<Student::GameState> gameState
            = std::shared_ptr<Student::GameState>(new Student::GameState());

    std::shared_ptr<Student::Player> player1
            = std::shared_ptr<Student::Player>(new Student::Player());
    */

    /*
    auto gameBoard2 = new Student::GameBoard();
    auto gameBoard3 = std::make_shared<Student::GameBoard>(gameBoard2);
    */


    std::shared_ptr<Student::GameBoard> gameBoard = std::make_shared<Student::GameBoard>();
    //std::shared_ptr<Common::IGameState> gameState = std::make_shared<Student::GameState>();

    std::vector<std::shared_ptr<Common::IPlayer>> playerVector;

    for( int a = 1; a < 6; a = a + 1 ){
        std::shared_ptr<Common::IPlayer> player1 = std::make_shared<Student::Player>(a);
        playerVector.push_back(player1);
    }


    //std::shared_ptr<Logic::GameEngine> gameEngine
      //      = std::shared_ptr<Logic::GameEngine>(new Logic::GameEngine(gameBoard, gameState, playerVector));


    //std::shared_ptr<Common::IGameRunner> gameRunner
            //= std::shared_ptr<Logic::GameEngine>(new Common::IGameRunner(gameBoard, gameState, playerVector));
    std::shared_ptr<Common::IGameRunner> gameRunner
            = Common::Initialization::getGameRunner(gameBoard, nullptr, playerVector);


    MainUI w(gameBoard);
    //w.initializeGameRunner(gameRunner);


    w.show();


    return a.exec();
}
