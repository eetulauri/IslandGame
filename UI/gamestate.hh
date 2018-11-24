#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "igamestate.hh"

namespace Student {

class GameState : public Common::IGameState
{
public:
    GameState();
    ~GameState();

    Common::GamePhase currentGamePhase() const;
    int currentPlayer() const;
    void changeGamePhase(Common::GamePhase nextPhase);
    void changePlayerTurn(int nextPlayer);

private:
    int currentPlayer_;
    Common::GamePhase current_;


};
}

#endif // GAMESTATE_HH
