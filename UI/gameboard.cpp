#include "gameboard.hh"


Student::GameBoard::GameBoard()
{

}

Student::GameBoard::~GameBoard()
{

}

int Student::GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{

}

bool Student::GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{

}

std::shared_ptr<Common::Hex> Student::GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{
    return nullptr;

}


void Student::GameBoard::addPawn(int playerId, int pawnId)
{

}

void Student::GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{

}

void Student::GameBoard::removePawn(int pawnId)
{

}

void Student::GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{

}

void Student::GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{

}

void Student::GameBoard::removeActor(int actorId)
{

}

void Student::GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    hexes_container_.push_back(newHex);
    Common::CubeCoordinate coord = newHex->getCoordinates();
    coordinates_.push_back(coord);
}

void Student::GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{

}

void Student::GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{

}

void Student::GameBoard::removeTransport(int id)
{

}

std::vector<std::shared_ptr<Common::Hex> > Student::GameBoard::returnHexesContainer()
{
    return hexes_container_;
}


