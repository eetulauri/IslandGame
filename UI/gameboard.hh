#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <QObject>

#include "igameboard.hh"
#include "graphichex.hh"
#include "actor.hh"
#include "transport.hh"
#include "player.hh"





namespace Student {



class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard() override;

    // Documentation in IgameBoard
    int checkTileOccupation(Common::CubeCoordinate tileCoord) const override;
    // Documentation in IgameBoard
    bool isWaterTile(Common::CubeCoordinate tileCoord) const override;
    // Documentation in IgameBoard
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const override;
    // Documentation in IgameBoard
    void addPawn(int playerId, int pawnId) override;
    // Documentation in IgameBoard
    void addPawn(int playerId, int pawnId, Common::CubeCoordinate coord) override;
    // Documentation in IgameBoard
    void movePawn(int pawnId, Common::CubeCoordinate pawnCoord) override;
    // Documentation in IgameBoard
    void removePawn(int pawnId) override;
    void addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord) override;
    // Documentation in IgameBoard
    void moveActor(int actorId, Common::CubeCoordinate actorCoord) override;
    // Documentation in IgameBoard
    void removeActor(int actorId) override;
    // Documentation in IgameBoard
    void addHex(std::shared_ptr<Common::Hex> newHex) override;
    // Documentation in IgameBoard
    void addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord) override;
    // Documentation in IgameBoard
    void moveTransport(int id, Common::CubeCoordinate coord) override;
    // Documentation in IgameBoard
    void removeTransport(int id) override;

    /**
     * @brief createPawns creates pawns to their designated corners
     */

    void createPawns();
    /**
     * @brief addPlayer stores player object into players_
     * @param player shared_ptr to player
     */
    void addPlayer(std::shared_ptr<Student::Player> player);

    /**
     * @brief getPlayerVector
     * @return vector of player objects
     */
    std::vector<std::shared_ptr<Student::Player> > getPlayerVector();

    /**
     * @brief calculateCornerPieces calculates the corners of the gameboard
     * and stores them in to a vector
     * @return vector to all the 6 possible corner pieces
     */
    std::vector<Common::CubeCoordinate> calculateCornerPieces();

    /**
     * @brief getHexesContainer
     * @return a map containing coordinate and corresponding hex
     */
    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> getHexesContainer();

    /**
     * @brief getPawnMap
     * @return a mapw containing pawns id and pawn shared_ptr to pawn object
     */
    std::unordered_map<int, std::shared_ptr<Common::Pawn>> getPawnMap();




private:

    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexesMap_;
    std::unordered_map<int, std::shared_ptr<Common::Pawn>> pawnMap_;
    std::unordered_map<int, std::shared_ptr<Common::Actor>> actorMap_;
    std::unordered_map<int, std::shared_ptr<Common::Transport>> transportMap_;
    std::vector<std::shared_ptr<Student::Player>> players_;


};
}
#endif // GAMEBOARD_HH
