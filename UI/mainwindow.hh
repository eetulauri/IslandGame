#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "graphichex.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "gameengine.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setScene();

    GameBoard *gameboard_;
    GameState *gamestate_;
    Logic::GameEngine *gameengine_;


};

#endif // MAINWINDOW_HH
