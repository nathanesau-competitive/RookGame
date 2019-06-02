#include <QSettings>

#include "cpuPlayer.h"
#include "gameController.h"
#include "utils.h"

GameController::GameController() : handInfo(roundInfo)
{
    clear();
}

void GameController::clear()
{
    overallInfo.clear();
    roundInfo.clear();
    handInfo.clear();

    deck.clear();
    nest.clear();

    playerArr.clear();

    map<int, string> playerNames = Utils::Db::readPlayerNamesFromDb();

    for(auto playerNum : vector<int>{PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4})
    {
        playerArr.push_back(Player(playerNum, playerNames[playerNum]));
    }
}

void GameController::onNewGame()
{
    clear();

    initializeDeck();
    dealDeck();
}

void GameController::onBid(int pBidAmount)
{
    playerArr[PLAYER_1].bid = pBidAmount;
    roundInfo.bidAmount = pBidAmount;

    for (auto playerNum : vector<int>{PLAYER_2, PLAYER_3, PLAYER_4})
    {
        playerArr[playerNum].bid = cpu.getBid(playerNum);

        if (playerArr[playerNum].bid > pBidAmount)
        {
            roundInfo.bidAmount = playerArr[playerNum].bid;
        }
    }

    if (getNumPassed() == 3)
    {
        roundInfo.bidPlayer = PLAYER_1;
        return;
    }
}

void GameController::onPass()
{
    playerArr[PLAYER_1].bid = 0;

    while (getNumPassed() != 3)
    {
        for (auto playerNum : vector<int>{PLAYER_2, PLAYER_3, PLAYER_4})
        {
            if (playerArr[playerNum].bid == 0 || playerArr[playerNum].bid != roundInfo.bidAmount)
            {
                playerArr[playerNum].bid = cpu.getBid(playerNum);
            }

            if (playerArr[playerNum].bid > roundInfo.bidAmount)
            {
                roundInfo.bidAmount = playerArr[playerNum].bid;
            }
        }
    }

    for (auto &player : playerArr)
    {
        if (player.bid != 0)
        {
            roundInfo.bidPlayer = player.playerNum;
            break;
        }
    }

    // 1. nest selection

    nest = cpu.getChosenNest(roundInfo.bidPlayer);

    CardVector &cardArr = playerArr[roundInfo.bidPlayer].cardArr;

    CardVector newCardArr;
    newCardArr.append({&nest, &cardArr});
    newCardArr.remove(nest);

    cardArr = newCardArr;

    // 2. trump selection

    roundInfo.trump = cpu.getChosenTrump(roundInfo.bidPlayer);

    // 3. partner selection

    roundInfo.partnerCard = cpu.getChosenPartner(roundInfo.bidPlayer);
}

void GameController::onStartGame()
{
    // todo
}

void GameController::playCard(Card cardPlayed, int playerNum)
{
    if (handInfo.startingPlayerNum == PLAYER_UNDEFINED) // first card played
    {
        handInfo.startingPlayerNum = playerNum;
        handInfo.suit = cardPlayed.suit;
    }

    handInfo.cardPlayed[playerNum] = cardPlayed;
    handInfo.points += cardPlayed.getPointValue();

    if (cardPlayed == roundInfo.partnerCard) // update partner and teams
    {
        roundInfo.partnerPlayerNum = playerNum;
        roundInfo.updateTeams();
    }

    playerArr[playerNum].cardArr.remove({cardPlayed});
}

void GameController::initializeDeck()
{
    vector<int> suitArr = {SUIT_BLACK, SUIT_GREEN, SUIT_RED, SUIT_YELLOW};
    vector<int> valueArr = {VALUE_1,
                            VALUE_2,
                            VALUE_3,
                            VALUE_4,
                            VALUE_5,
                            VALUE_6,
                            VALUE_7,
                            VALUE_8,
                            VALUE_9,
                            VALUE_10,
                            VALUE_11,
                            VALUE_12,
                            VALUE_13,
                            VALUE_14};

    for (auto suit : suitArr)
    {
        for (auto value : valueArr)
        {
            deck.push_back(Card(suit, value));
        }
    }

    deck.push_back(Card(SUIT_SPECIAL, VALUE_ROOK));

    auto seed = 1009;
    //auto seed = (int)chrono::system_clock::now().time_since_epoch().count();

    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

void GameController::dealDeck()
{
    int playerNum = PLAYER_1;

    while (deck.size() > 5)
    {
        Card currentCard = deck.back(); // copy
        deck.pop_back();

        playerArr[playerNum].cardArr.push_back(currentCard);
        playerNum = playerArr[playerNum].getNextPlayerNum();
    }

    while (deck.size() > 0)
    {
        Card currentCard = deck.back(); // copy
        deck.pop_back();

        nest.push_back(currentCard);
    }

    nest.sort();
    playerArr[PLAYER_1].cardArr.sort();
}

int GameController::getNumPassed()
{
    int numPassed = 0;

    for (auto &player : playerArr)
    {
        if (player.bid == 0)
        {
            numPassed++;
        }
    }

    return numPassed;
}

bool GameController::isRoundOver()
{
    for (auto playerNum : vector<int>{PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4})
    {
        if (!playerArr[playerNum].cardArr.empty())
        {
            return false;
        }
    }

    return true;
}