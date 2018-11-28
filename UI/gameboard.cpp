#include "gameboard.hh"


Student::GameBoard::GameBoard()
{

}

Student::GameBoard::~GameBoard()
{

}

int Student::GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{


    std::shared_ptr<Common::Hex> hex = getHex(tileCoord);
    if (hex == nullptr) {
        return -1;
    } else {
        int amount = hex->getPawnAmount();
        return amount;
    }


}

bool Student::GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{

    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate coord = it->first;
        if (coord == tileCoord)
        {
            std::shared_ptr<Common::Hex> hex = it->second;
            if (hex->isWaterTile())
            {
                return true;
            } else {
                return false;
            }

        }
    }
    return false;
}

std::shared_ptr<Common::Hex> Student::GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{

    for (const auto &element : hexesMap_)
    {
        if (element.first == hexCoord)
        {
            return element.second;
        }
    }
    return nullptr;
}


void Student::GameBoard::addPawn(int playerId, int pawnId)
{
    std::shared_ptr<Common::Pawn> pawn = std::make_shared<Common::Pawn>();
    pawn->setId(pawnId, playerId);
    pawnMap_[pawnId] = pawn;
}

void Student::GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Pawn> pawn = std::make_shared<Common::Pawn>();
    pawn->setId(pawnId, playerId);
    pawn->setCoordinates(coord);
    pawnMap_[pawnId] = pawn;
    std::shared_ptr<Common::Hex> hex = getHex(coord);
    hex->addPawn(pawn);

}

void Student::GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{

    std::shared_ptr<Common::Hex> newHex = getHex(pawnCoord);

    if (newHex != nullptr)
    {
        for (const auto &element : pawnMap_)
        {
            if (element.first == pawnId)
            {
                std::shared_ptr<Common::Pawn> pawn = element.second;
                std::shared_ptr<Common::Hex> oldHex = getHex(pawn->getCoordinates());
                oldHex->removePawn(pawn);
                newHex->addPawn(pawn);
                pawn->setCoordinates(pawnCoord);
            }
        }
    }

}

void Student::GameBoard::removePawn(int pawnId)
{

    for (const auto &element : pawnMap_)
    {
        if (element.first == pawnId)
        {
            std::shared_ptr<Common::Pawn> pawn = element.second;
            std::shared_ptr<Common::Hex> hex = getHex(pawn->getCoordinates());
            if (hex != nullptr)
            {
                hex->removePawn(pawn);
            }
            pawnMap_.erase(pawnId);
            return;
        }
    }
}

void Student::GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{

    actorMap_[actor->getId()] = actor;
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate hexCoord = it->first;
        if (hexCoord == actorCoord)
        {

            actor->addHex(it->second);
        }
    }

}

void Student::GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate hexCoord = it->first;
        if (hexCoord == actorCoord)
        {
            std::shared_ptr<Common::Actor> actor;
            for (auto &actorid : actorMap_)
            {
                if (actorid.first == actorId)
                {
                    actor = actorid.second;
                }
            }
            actor->move(it->second);
        }
    }

}

void Student::GameBoard::removeActor(int actorId)
{
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        std::vector<std::shared_ptr<Common::Actor> > actors = it->second->getActors();
        for (auto &actor : actors)
        {
            if (actor->getId() == actorId)
            {
                it->second->removeActor(actor);
            }
        }
    }

}

void Student::GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    Common::CubeCoordinate coord = newHex->getCoordinates();
    hexesMap_[coord] = newHex;
}

void Student::GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{

    transportMap_[transport->getId()] = transport;
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate hexCoord = it->first;
        if (hexCoord == coord)
        {

            transport->addHex(it->second);
        }
    }


}

void Student::GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate hexCoord = it->first;
        if (hexCoord == coord)
        {
            std::shared_ptr<Common::Transport> transport;
            for (auto &transportId : transportMap_)
            {
                if (transportId.first == id)
                {
                    transport = transportId.second;
                }

            }
            transport->move(it->second);

        }
    }

}

void Student::GameBoard::removeTransport(int id)
{
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        std::vector<std::shared_ptr<Common::Transport> > transports = it->second->getTransports();
        for (auto &transport : transports)
        {
            if (transport->getId() == id)
            {
                it->second->removeTransport(transport);
                return;
            }
        }
    }

}

void Student::GameBoard::createPawns()
{
    std::vector<Common::CubeCoordinate> cornerPieces = calculateCornerPieces();

    for (long unsigned int i = 1; i < players_.size()+1; i++) {
        addPawn(i, i, cornerPieces.at(i-1));
    }


}

void Student::GameBoard::addPlayer(std::shared_ptr<Student::Player> player)
{
    players_.push_back(player);
}

std::vector<std::shared_ptr<Common::IPlayer> > Student::GameBoard::getPlayerVector()
{
    return players_;
}



std::vector<Common::CubeCoordinate> Student::GameBoard::calculateCornerPieces()
{
    std::vector<Common::CubeCoordinate> cornerPieces;
    for (auto &element : hexesMap_) {
        if (element.second->getPieceType() == "Coral" and (element.first.x == 0 or element.first.y == 0 or element.first.z == 0)) {
            cornerPieces.push_back(element.first);
        }
    }
    return cornerPieces;
}

std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex> > Student::GameBoard::getHexesContainer()
{
    return hexesMap_;
}


