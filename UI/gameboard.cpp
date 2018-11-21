#include "gameboard.hh"


Student::GameBoard::GameBoard()
{

}

Student::GameBoard::~GameBoard()
{

}

int Student::GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{
    /*
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
    */

    std::shared_ptr<Common::Hex> hex = getHex(tileCoord);
    if (hex == nullptr) {
        return -1;
    } else {
        return hex->getPawnAmount();
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
    std::shared_ptr<Common::Pawn> pawn = std::make_shared<Common::Pawn>();
    pawn->setId(pawnId, playerId);
    pawns_.push_back(pawn);
}

void Student::GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Pawn> pawn = std::make_shared<Common::Pawn>();
    pawn->setId(playerId, pawnId);
    pawn->setCoordinates(coord);
    pawns_.push_back(pawn);
    pawnMap_[pawnId] = pawn;

    /*
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate hexCoord = it->first;
        if (hexCoord == coord)
        {
            it->second->addPawn(pawn);
        }
    }
    */
    std::shared_ptr<Common::Hex> hex = getHex(coord);
    hex->addPawn(pawn);

}

void Student::GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    /*
    std::shared_ptr<Common::Pawn> pawn2;
    for (auto &pawn : pawns_)
    {
        if (pawn->getId() == pawnId)
        {
            pawn->setCoordinates(pawnCoord);
            pawn2 = pawn;

        }
    }

    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate hexCoord = it->first;
        if (hexCoord == pawnCoord)
        {
            it->second->addPawn(pawn2);
        }
    }

    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        Common::CubeCoordinate hexCoord = it->first;
        if (hexCoord == pawnCoord)
        {
            std::shared_ptr<Common::Pawn> pawn2;
            //std::shared_ptr<Common::Transport> transport = it->second->giveTransport(id);
            for (auto &pawn : pawnMap_)
            {
                if (pawn.first == pawnId)
                {
                    pawn2 = pawn.second;
                }

            }
            it->second->addPawn(pawn2);

        }
    }
    */
    std::shared_ptr<Common::Hex> newHex = getHex(pawnCoord);

    if (newHex != nullptr)
    {
        for (auto &element : pawnMap_)
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
    /*
    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        std::vector<std::shared_ptr<Common::Pawn> > pawns = it->second->getPawns();
        for (auto &pawn : pawns)
        {
            if (pawn->getId() == pawnId)
            {
                it->second->removePawn(pawn);
                // TO DO:

                //might also need to remove pawn from pawns_ (????)
            }
        }
    }


    for (std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>::const_iterator it =hexesMap_.begin(); it!=hexesMap_.end(); ++it)
    {
        std::vector<std::shared_ptr<Common::Pawn> > pawns = it->second->getPawns();
        for (auto &pawn : pawns)
        {
            if (pawn->getId() == pawnId)
            {
                it->second->removePawn(pawn);
            }
        }
    }
    */
    for (auto &element : pawnMap_)
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
            //std::shared_ptr<Common::Actor> actor = it->second->giveActor(actorId);
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
    hexes_container_.push_back(newHex);
    Common::CubeCoordinate coord = newHex->getCoordinates();
    coordinates_.push_back(coord);
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
            //std::shared_ptr<Common::Transport> transport = it->second->giveTransport(id);
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

std::vector<std::shared_ptr<Common::Hex> > Student::GameBoard::getHexesContainer()
{
    return hexes_container_;
}


