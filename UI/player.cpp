#include "player.hh"


Student::Player::Player(int id) :
    playerId_(id),
    actionsLeft_(100)
{
}

Student::Player::~Player()
{

}

int Student::Player::getPlayerId() const
{
    return playerId_;
}

void Student::Player::setActionsLeft(unsigned int actionsLeft)
{
    actionsLeft_ = actionsLeft;
}

unsigned int Student::Player::getActionsLeft() const
{
    return actionsLeft_;
}
