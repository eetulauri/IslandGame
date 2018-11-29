#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"
#include "cubecoordinate.hh"


namespace Student {



class Player : public Common::IPlayer
{
public:
    Player(int id);
    ~Player();

    int getPlayerId() const;
    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft() const;
    void addToMovesUsed();
    int getMovesUsed();
    void setStartingCoordinates(Common::CubeCoordinate coord);
    Common::CubeCoordinate getStartingCoordinates();


private:
    int playerId_;
    int actionsLeft_;
    int movesUsedCounter_;
    Common::CubeCoordinate startingCoordinates_;

};
}

#endif // PLAYER_HH
