#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"

namespace Student {



class Player : public Common::IPlayer
{
public:
    Player(int id);
    ~Player();

    int getPlayerId() const;
    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft() const;


private:
    int playerId_;
    int actionsLeft_;

};
}

#endif // PLAYER_HH
