#ifndef MAINUI_HH
#define MAINUI_HH

#include "graphichex.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "gameengine.hh"
#include "igamerunner.hh"

#include <QMainWindow>

namespace Ui {
class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainUI(std::shared_ptr<Student::GameBoard> gameBoard,
                    std::shared_ptr<Student::GameState> gameState,
                    QWidget *parent = 0);
    ~MainUI();

    void drawHex();


private:
    Ui::MainUI *ui;
    QGraphicsScene *scene_;
    std::shared_ptr<Student::GameBoard> gameBoard_;
    std::shared_ptr<Student::GameState> gameState_;

};

#endif // MAINUI_HH
