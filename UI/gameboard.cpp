#include "gameboard.hh"


GameBoard::GameBoard() :
    scene_(new QGraphicsScene)
{

}

GameBoard::~GameBoard()
{

}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    hexes_container_.push_back(newHex);
    GraphicHex *graphic_hex = new GraphicHex();
    scene_->addItem(graphic_hex);

}
