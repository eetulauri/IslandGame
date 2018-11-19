#include "gameboard.hh"


Student::GameBoard::GameBoard()
{

}

Student::GameBoard::~GameBoard()
{

}

int Student::GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate coord = it->first;
        if (coord == tileCoord)
        {
            std::shared_ptr<Common::Hex> hex = it->second;
            return hex->getPawnAmount();
        }
    }
    int noPawns = -1;
    return noPawns;
}

bool Student::GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{
    std::string water = "Water";

    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate coord = it->first;
        if (coord == tileCoord)
        {
            std::shared_ptr<Common::Hex> hex = it->second;
            if (hex->getPieceType() == water)
            {
                return true;
            }

        }
    }
    return false;
}

std::shared_ptr<Common::Hex> Student::GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate coord = it->first;
        if (coord == hexCoord)
        {
            return it->second;
        }
    }

    return nullptr;
}


void Student::GameBoard::addPawn(int playerId, int pawnId)
{
    //Common::Pawn *pawn = new Common::Pawn(playerId, pawnId);
    std::shared_ptr<Common::Pawn> pawn = std::make_shared<Common::Pawn>(playerId, pawnId);
    pawns_.push_back(pawn);
}

void Student::GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    //Common::Pawn *pawn = new Common::Pawn(playerId, pawnId, coord);
    std::shared_ptr<Common::Pawn> pawn = std::make_shared<Common::Pawn>(playerId, pawnId, coord);
    pawns_.push_back(pawn);
}

void Student::GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    for (auto &pawn : pawns_)
    {
        if (pawn->getId() == pawnId)
        {
            pawn->setCoordinates(pawnCoord);
        }
    }
}

void Student::GameBoard::removePawn(int pawnId)
{
    for (auto &pawn : pawns_)
    {
        if (pawn->getId() == pawnId)
        {
            // TO DO:

            //might also need to remove pawn from pawns_ (????)
            
            delete &pawn;
        }
    }

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
    hexesMap_[coord] = newHex;

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

std::vector<std::shared_ptr<Common::Hex> > Student::GameBoard::getHexesContainer()
{
    return hexes_container_;
}


