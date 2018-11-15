#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"

namespace Student {



class Player : public Common::IPlayer
{
public:
    Player();
    ~Player();

    int getPlayerId() const;
    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft() const;

};
}

#endif // PLAYER_HH
