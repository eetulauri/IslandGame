#ifndef MAINUI_HH
#define MAINUI_HH

#include "graphichex.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "gameengine.hh"
#include "igamerunner.hh"
#include "cubecoordinate.hh"
#include "hex.hh"
#include "igameboard.hh"

#include "iostream"

#include <QMainWindow>
#include <unordered_map>
#include <string>


namespace Ui {
class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainUI(std::shared_ptr<Student::GameBoard> gameBoard,
                    QWidget *parent = 0);
    ~MainUI();

    void drawHex();
    QPoint cube_to_axial(Common::CubeCoordinate coord);
    QPointF axial_to_pixel(QPoint point,int size);


private:
    Ui::MainUI *ui;
    QGraphicsScene *scene_;
    std::shared_ptr<Student::GameBoard> gameBoard_;
    std::shared_ptr<Common::IGameState> gameState_;

};

#endif // MAINUI_HH
