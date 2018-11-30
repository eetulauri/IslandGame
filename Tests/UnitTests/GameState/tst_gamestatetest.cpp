#include <QString>
#include <QtTest>
#include <vector>

#include "gamestate.hh"
#include "hex.hh"
#include "pawn.hh"
#include "transport.hh"
#include "dolphin.hh"
#include "boat.hh"
#include "actor.hh"
#include "kraken.hh"
#include "seamunster.hh"
#include "shark.hh"
#include "vortex.hh"


class GameStateTest : public QObject
{
    Q_OBJECT

public:
    GameStateTest();

private:
    std::shared_ptr<Student::GameState> gameState_;

private Q_SLOTS:
    void init();
    void testGamePhase();
    void testCurrentPlayer();
};

GameStateTest::GameStateTest() :
    gameState_(nullptr)
{
}

void GameStateTest::init()
{
    gameState_.reset();
    gameState_ = std::make_shared<Student::GameState>();
}

void GameStateTest::testGamePhase()
{
    gameState_->changeGamePhase(Common::SINKING);
    QVERIFY(gameState_->currentGamePhase() == Common::SINKING);
}

void GameStateTest::testCurrentPlayer()
{
    gameState_->changePlayerTurn(2);
    QVERIFY(gameState_->currentPlayer() == 2);
}





QTEST_APPLESS_MAIN(GameStateTest)

#include "tst_gamestatetest.moc"
