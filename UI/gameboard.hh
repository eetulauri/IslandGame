#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>

#include "igameboard.hh"

class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();

    void addHex(std::shared_ptr<Common::Hex> newHex) = 0;

};
#endif // GAMEBOARD_HH
