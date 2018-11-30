#include <QString>
#include <QtTest>
#include <vector>

#include "player.hh"
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

class PlayerTest : public QObject
{
    Q_OBJECT

public:
    PlayerTest();

private:
    std::shared_ptr<Student::Player> player_;

private Q_SLOTS:
    void init();
    void testId();
    void testSetActionsLeft();
    void testMovesUsed();
    void testPawnKills();
};

PlayerTest::PlayerTest() :
    player_(nullptr)
{
}

void PlayerTest::init()
{
    player_.reset();
    player_ = std::make_shared<Student::Player>(1);
}

void PlayerTest::testId()
{
    QVERIFY(player_->getPlayerId() == 1);
}

void PlayerTest::testSetActionsLeft()
{
    player_->setActionsLeft(3);
    QVERIFY(player_->getActionsLeft() == 3);
}

void PlayerTest::testMovesUsed()
{
    player_->addToMovesUsed();
    player_->addToMovesUsed();
    QVERIFY(player_->getMovesUsed() == 2);
}

void PlayerTest::testPawnKills()
{
    player_->addToPawnKills();
    player_->addToPawnKills();
    QVERIFY(player_->getPawnKills() == 2);
}

QTEST_APPLESS_MAIN(PlayerTest)

#include "tst_playertest.moc"
