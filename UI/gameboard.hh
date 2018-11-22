#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "igameboard.hh"
#include "graphichex.hh"
#include "actor.hh"
#include "transport.hh"



namespace Student {



class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard() override;

    int checkTileOccupation(Common::CubeCoordinate tileCoord) const override;
    bool isWaterTile(Common::CubeCoordinate tileCoord) const override;
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const override;
    void addPawn(int playerId, int pawnId) override;
    void addPawn(int playerId, int pawnId, Common::CubeCoordinate coord) override;
    void movePawn(int pawnId, Common::CubeCoordinate pawnCoord) override;
    void removePawn(int pawnId) override;
    void addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord) override;
    void moveActor(int actorId, Common::CubeCoordinate actorCoord) override;
    void removeActor(int actorId) override;

    void addHex(std::shared_ptr<Common::Hex> newHex) override;
    void addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord) override;
    void moveTransport(int id, Common::CubeCoordinate coord) override;
    void removeTransport(int id) override;

    std::vector<std::shared_ptr<Common::Hex>> getHexesContainer();

private:

    std::vector<std::shared_ptr<Common::Hex>> hexes_container_;
    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexesMap_;
    std::unordered_map<int, std::shared_ptr<Common::Pawn>> pawnMap_;
    std::unordered_map<int, std::shared_ptr<Common::Actor>> actorMap_;
    std::unordered_map<int, std::shared_ptr<Common::Transport>> transportMap_;

};
}
#endif // GAMEBOARD_HH
