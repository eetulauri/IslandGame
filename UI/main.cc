#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "mainwindow.hh"
#include "igamerunner.hh"
#include "initialize.hh"
#include "mainui.hh"

#include <memory>
#include <iostream>
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    std::shared_ptr<Student::GameBoard> gameBoard
            = std::shared_ptr<Student::GameBoard>(new Student::GameBoard());
    std::shared_ptr<Student::GameState> gameState
            = std::shared_ptr<Student::GameState>(new Student::GameState());
    //std::shared_ptr<Logic::GameEngine> gameEngine
            //= std::shared_ptr<Logic::GameEngine>(new Logic::GameEngine(gameBoard, gameState));

    std::vector<std::shared_ptr<Common::IPlayer>> playerVector;
    //std::shared_ptr<Common::IGameRunner> gameRunner = std::shared_ptr<Logic::GameEngine>(new Common::IGameRunner(gameBoard, gameState, playerVector));
    //std::shared_ptr<Common::IGameRunner> gameRunner = Common::Initialization::getGameRunner(gameBoard, gameState, playerVector);



    //std::shared_ptr<QGraphicsView> view = std::shared_ptr<QGraphicsView>(new QGraphicsView());
    //std::shared_ptr<QGraphicsScene> scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene());



    MainUI w;
    //w.initializeGameRunner(gameRunner);
    w.show();


    return a.exec();
}
