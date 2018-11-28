#include "gamestate.hh"



Student::GameState::GameState() :
    current_(Common::MOVEMENT),
    currentPlayer_(1)
{

}

Student::GameState::~GameState()
{

}

Common::GamePhase Student::GameState::currentGamePhase() const
{
    return current_;
}

int Student::GameState::currentPlayer() const
{
    return currentPlayer_;
}

void Student::GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    current_ = nextPhase;
}

void Student::GameState::changePlayerTurn(int nextPlayer)
{
    currentPlayer_ = nextPlayer;
}
