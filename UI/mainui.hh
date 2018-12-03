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
#include <chrono>
#include <thread>
#include <QWheelEvent>


namespace Ui {
class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainUI is the mainwindow of the program
     * @param gameBoard shared_ptr to gameBoard
     * @param gameRunner shared_ptr to gameRunner
     * @param gameState shared_ptr to gameState
     * @param parent
     */
    explicit MainUI(std::shared_ptr<Student::GameBoard> gameBoard,
                    std::shared_ptr<Common::IGameRunner> gameRunner,
                    std::shared_ptr<Student::GameState> gameState,
                    QWidget *parent = 0);
    ~MainUI();

    /**
     * @brief drawHex draws the hexes to the gameboard. Creates new
     * graphicHex type objects which are then added to the scene. Also
     * connect the singal which is emitted when hex is clicked.
     */
    void drawHex();

    /**
     * @brief cube_to_axial transforms cube coordinates to axial
     * @param coord
     * @return QPoint of x, y coordinates
     */
    QPoint cube_to_axial(Common::CubeCoordinate coord);

    /**
     * @brief axial_to_pixel transforms axial coordinates to pixel locations
     * @param point is x, y coordinates in axial
     * @param size is predetermined size for hexagon
     * @return QPointF pixel location
     */
    QPointF axial_to_pixel(QPoint point,int size);

    /**
     * @brief getCorrespondingGraphicHex returns the corresponding
     * @param hex
     * @return
     */
    GraphicHex* getCorrespondingGraphicHex(std::shared_ptr<Common::Hex> hex);

    /**
     * @brief gamePhaseMovement determines if its the 1st click or
     * the 2nd click and does actions accordingly
     * @param hex which is clicked
     */
    void gamePhaseMovement(std::shared_ptr<Common::Hex> hex);

    /**
     * @brief gamePhaseSinking flips the clicked tile if permitted
     * @param hex which is clicked and possibly flipped
     */
    void gamePhaseSinking(std::shared_ptr<Common::Hex> hex);

    /**
     * @brief gamePhaseSpinning determines if its the 1st or 2nd click and
     * does actions accordingly
     * @param hex which is clicked
     */
    void gamePhaseSpinning(std::shared_ptr<Common::Hex> hex);

    /**
     * @brief printCurrentPlayerTurn prints the current players turn
     * to the textedit box in mainUi
     */
    void printCurrentPlayerTurn();

    /**
     * @brief checkIfPlayerHasWon checks if the player has moved
     * to the centre square and acts accordingly
     * @param hex which is the destination for the pawn
     */
    void checkIfPlayerHasWon(std::shared_ptr<Common::Hex> hex);

    /**
     * @brief spawnNewPawn is called when a pawn dies and a new one
     * is need at the players base coordinates
     * @param playerId is the player whose pawn needs to be respanwed
     */
    void spawnNewPawn(int playerId);




public slots:

    /**
     * @brief hexClicked determines which gamephase the game is on
     * when a hex is clicked and forward the clicked hex to to correct
     * method
     * @param hex which is clicked
     */
    void hexClicked(std::shared_ptr<Common::Hex> hex);

    /**
     * @brief nextPhase changes the gamePhase to the next one
     * also changes players if going from SPINNING to MOVEMENT
     */
    void nextPhase();

    /**
     * @brief spinWheel spins the wheel and displays the result graphically
     * saves the result in wheel_ for later use
     */
    void spinWheel();

protected:

    /**
     * @brief wheelEvent is for zooming in and out of the game using
     * scroll wheel
     * @param event
     */
    virtual void wheelEvent(QWheelEvent* event);

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
