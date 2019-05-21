#include "cpuPlayer.h"
#include "gameController.h"
#include "utils.h"

GameController::GameController()
{
    clear();
}

void GameController::clear()
{
    deck.clear();
    playerArr.clear();
    nest.clear();

    currentTurn = PLAYER_UNDEFINED;
    bidAmount = 0;
    bidPlayer = PLAYER_UNDEFINED;
    phase = PHASE_UNDEFINED;
    trump = SUIT_UNDEFINED;
    pointsMiddle = 0;
    partnerPair = make_pair(Card(SUIT_UNDEFINED, VALUE_UNDEFINED), PLAYER_UNDEFINED);
    handInfo.clear();
    teams.first.clear();
    teams.second.clear();
    
    for(auto playerNum : vector<int>{PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4})
    {
        playerScores[playerNum] = 0;
    }
    
    for(auto teamNum : vector<int>{TEAM_1, TEAM_2})
    {
        teamScores[teamNum] = 0;
    }
}

void GameController::newGame()
{
    clear();

    initializeDeck();
    initializePlayerArr();
    dealDeck();

    phase = PHASE_BID;
}

void GameController::bid(int pBidAmount)
{
    playerArr[PLAYER_1].bid = pBidAmount;
    bidAmount = pBidAmount;

    vector<int> playerNumArr = {PLAYER_2, PLAYER_3, PLAYER_4}; // cpu players

    for (auto playerNum : playerNumArr)
    {
        playerArr[playerNum].bid = cpu.getBid(playerNum);

        if (playerArr[playerNum].bid > pBidAmount)
        {
            bidAmount = playerArr[playerNum].bid;
        }
    }

    if (getNumPassed() == 3)
    {
        bidPlayer = PLAYER_1;
        phase = PHASE_MIDDLE;
        return;
    }
}

void GameController::pass()
{
    playerArr[PLAYER_1].bid = 0;

    while (getNumPassed() != 3)
    {
        vector<int> playerNumArr = {PLAYER_2, PLAYER_3, PLAYER_4}; // cpu players

        for (auto playerNum : playerNumArr)
        {
            if (playerArr[playerNum].bid == 0 || playerArr[playerNum].bid != bidAmount)
            {
                playerArr[playerNum].bid = cpu.getBid(playerNum);
            }

            if (playerArr[playerNum].bid > bidAmount)
            {
                bidAmount = playerArr[playerNum].bid;
            }
        }
    }

    for (auto &player : playerArr)
    {
        if (player.bid != 0)
        {
            bidPlayer = player.playerNum;
            phase = PHASE_MIDDLE;
            return;
        }
    }
}

void GameController::startGame()
{
    phase = PHASE_PLAY;

    // todo
}

void GameController::playHand(Card cardPlayed)
{
    auto removePlayedCardFromHand = [&](int playerNum) {
        Card card = handInfo.cardPlayed[playerNum];

        auto &cardArr = playerArr[playerNum].cardArr;
        auto cardIt = std::find(cardArr.begin(), cardArr.end(), card);
        cardArr.erase(cardIt);
    };

    handInfo.clear();

    handInfo.cardPlayed[PLAYER_1] = cardPlayed;
    handInfo.points += cardPlayed.getPointValue();
    handInfo.suit = cardPlayed.suit;

    removePlayedCardFromHand(PLAYER_1);

    vector<int> playerNumArr = {PLAYER_2, PLAYER_3, PLAYER_4}; // cpu players

    for (auto playerNum : playerNumArr)
    {
        Card cardToPlay = cpu.getCardToPlay(playerNum);

        handInfo.cardPlayed[playerNum] = cardToPlay;
        handInfo.points += cardToPlay.getPointValue();

        removePlayedCardFromHand(playerNum);
    }

    pair<Card, int> winningPair = handInfo.getWinningPair();

    playerScores[winningPair.second] += handInfo.points;

    if(playerArr[PLAYER_1].cardArr.empty())
    {
        playerScores[winningPair.second] += gc.pointsMiddle;
    }
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

    auto seed = (int)chrono::system_clock::now().time_since_epoch().count();

    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

void GameController::initializePlayerArr()
{
    vector<int> playerNumArr = {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4};

    for (auto playerNum : playerNumArr)
    {
        playerArr.push_back(Player(playerNum));
    }
}

void GameController::dealDeck()
{
    int playerNum = PLAYER_1;

    while (deck.size() > 5)
    {
        Card currentCard = deck.back(); // copy
        deck.pop_back();

        playerArr[playerNum].cardArr.push_back(currentCard);
        Utils::Game::incrementPlayerNum(playerNum);
    }

    while (deck.size() > 0)
    {
        Card currentCard = deck.back(); // copy
        deck.pop_back();

        nest.push_back(currentCard);
    }

    Utils::Game::sortCardArray(nest);
    Utils::Game::sortCardArray(playerArr[PLAYER_1].cardArr);
}

int GameController::getNumPassed()
{
    int numPassed = 0;

    for (auto &player : gc.playerArr)
    {
        if (player.bid == 0)
        {
            numPassed++;
        }
    }

    return numPassed;
}