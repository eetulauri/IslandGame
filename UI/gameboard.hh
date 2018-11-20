#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <string>
#include <memory>
#include <iostream>

#include "igameboard.hh"
#include "graphichex.hh"
#include "pawn.hh"
#include "actor.hh"
#include "transport.hh"
#include "hex.hh"


namespace Student {



class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();




    int checkTileOccupation(Common::CubeCoordinate tileCoord) const;
    bool isWaterTile(Common::CubeCoordinate tileCoord) const;
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const;
    void addPawn(int playerId, int pawnId);
    void addPawn(int playerId, int pawnId, Common::CubeCoordinate coord);
    void movePawn(int pawnId, Common::CubeCoordinate pawnCoord);
    void removePawn(int pawnId);
    void addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord);
    void moveActor(int actorId, Common::CubeCoordinate actorCoord);
    void removeActor(int actorId);

    void addHex(std::shared_ptr<Common::Hex> newHex);
    void addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord);
    void moveTransport(int id, Common::CubeCoordinate coord);
    void removeTransport(int id);

    std::vector<std::shared_ptr<Common::Hex>> getHexesContainer();

private:

    std::vector<std::shared_ptr<Common::Hex>> hexes_container_;
    std::vector<Common::CubeCoordinate> coordinates_;
    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexesMap_;
    std::vector<std::shared_ptr<Common::Pawn>> pawns_;
    std::map<int, std::shared_ptr<Common::Pawn>> pawnMap_;
    std::map<int, std::shared_ptr<Common::Actor>> actorMap_;
    std::map<int, std::shared_ptr<Common::Transport>> transportMap_;

};
}
#endif // GAMEBOARD_HH
