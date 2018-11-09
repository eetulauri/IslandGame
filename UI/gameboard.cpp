#include "gameboard.hh"


Student::GameBoard::GameBoard()
    //scene_(new QGraphicsScene)
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

void Student::GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{

}

void Student::GameBoard::removeActor(int actorId)
{

}

void Student::GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    hexes_container_.push_back(newHex);
    GraphicHex *graphic_hex = new GraphicHex();
    //scene_->addItem(graphic_hex);

}
