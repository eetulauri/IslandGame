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
#include "illegalmoveexception.hh"


#include <iostream>
#include <QMainWindow>
#include <unordered_map>
#include <string>
#include <QObject>
#include <QString>
#include <QDialog>
#include <QMessageBox>
#include <QPixmap>
#include <random>
#include <memory>


namespace Ui {
class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainUI(std::shared_ptr<Student::GameBoard> gameBoard,
                    std::shared_ptr<Common::IGameRunner> gameRunner,
                    std::shared_ptr<Student::GameState> gameState,
                    QWidget *parent = 0);
    ~MainUI();

    void drawHex();
    QPoint cube_to_axial(Common::CubeCoordinate coord);
    QPointF axial_to_pixel(QPoint point,int size);
    GraphicHex* getCorrespondingGraphicHex(std::shared_ptr<Common::Hex> hex);

    void gamePhaseMovement(std::shared_ptr<Common::Hex> hex);
    void gamePhaseSinking(std::shared_ptr<Common::Hex> hex);
    void gamePhaseSpinning(std::shared_ptr<Common::Hex> hex);

    void printCurrentPlayerTurn();

    void checkIfPlayerHasWon(std::shared_ptr<Common::Hex> hex);

    void spawnNewPawn(int playerId);




public slots:

    void givePawnNewCoordinates(std::shared_ptr<Common::Hex> hex);
    void nextPhase();
    void spinWheel();



private:
    Ui::MainUI *ui;
    QGraphicsScene *scene_;
    std::shared_ptr<Student::GameBoard> gameBoard_;
    std::shared_ptr<Common::IGameRunner> gameRunner_;
    std::shared_ptr<Common::IGameState> gameState_;

    std::shared_ptr<Common::Hex> selectedHex_;
    std::shared_ptr<Common::Pawn> pawn_;
    std::shared_ptr<Common::Actor> actor_;
    std::shared_ptr<Common::Transport> transport_;
    std::vector<GraphicHex*> graphicHexesVector_;
    std::pair<std::string, std::string> wheel_;
    bool moveActors_;
};

#endif // MAINUI_HH
