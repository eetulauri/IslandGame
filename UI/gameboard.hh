#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "igameboard.hh"
#include "graphichex.hh"

class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();

    void addHex(std::shared_ptr<Common::Hex> newHex);

private:

    std::vector<std::shared_ptr<Common::Hex>> hexes_container_;

    QGraphicsScene *scene_;

};
#endif // GAMEBOARD_HH
