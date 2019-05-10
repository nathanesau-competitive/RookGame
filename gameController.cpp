#include "gameController.h"
#include "cpuPlayer.h"

Card::Card(int pSuit, int pValue) : suit(pSuit), value(pValue)
{
}

bool Card::operator==(const Card &p)
{
    return p.value == value && p.suit == suit;
}

Player::Player(const int pPlayerNum) : playerNum(pPlayerNum)
{
    bid = 0;
}

// global functions
void sortCardArray(vector<Card> &cardArr)
{
    struct CardCompareValue
    {
        inline bool operator()(const Card &card1, const Card &card2)
        {
            return card1.value < card2.value;
        }
    };

    struct CardCompareSuit
    {
        inline bool operator()(const Card &card1, const Card &card2)
        {
            return card1.suit < card2.suit;
        }
    };

    sort(cardArr.begin(), cardArr.end(), CardCompareValue());
    sort(cardArr.begin(), cardArr.end(), CardCompareSuit());
}

// used for auto-selecting middle cards
vector<SuitInfo> getSuitInfoArr(vector<Card> &cardArr)
{
    struct SuitInfoCompareCount // ascending order
    {
        inline bool operator()(const SuitInfo &info1, const SuitInfo &info2)
        {
            return info1.count > info2.count;
        }
    };

    struct SuitInfoCompareTotalValue // ascending order
    {
        inline bool operator()(const SuitInfo &info1, const SuitInfo &info2)
        {
            return info1.totalValue > info2.totalValue;
        }
    };

    vector<int> suitArr = {SUIT_BLACK, SUIT_GREEN, SUIT_RED, SUIT_YELLOW, SUIT_SPECIAL};
    vector<SuitInfo> suitInfoArr;

    for (auto suit : suitArr)
    {
        suitInfoArr.push_back(SuitInfo(suit));
    }

    for (auto &card : gc.playerArr[PLAYER_1].cardArr)
    {
        auto It = std::find(suitInfoArr.begin(), suitInfoArr.end(), SuitInfo(card.suit));

        if (card.suit == SUIT_SPECIAL)
        {
            It->count += 1;
            It->totalValue = 100; // ALWAYS keep this card (TRUMP)
        }
        else
        {
            It->count += 1;
            It->totalValue += card.value;
        }
    }

    sort(suitInfoArr.begin(), suitInfoArr.end(), SuitInfoCompareCount());
    sort(suitInfoArr.begin(), suitInfoArr.end(), SuitInfoCompareTotalValue());

    return suitInfoArr;
}

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
    currentBid = 0;
    winningBidder = PLAYER_UNDEFINED;
    currentPhase = PHASE_UNDEFINED;
    trump = SUIT_UNDEFINED;
}

void GameController::newGame()
{
    clear();

    initializeDeck();
    initializePlayerArr();
    dealDeck();

    currentTurn = PLAYER_UNDEFINED;
    currentBid = 0;
    winningBidder = PLAYER_UNDEFINED;
    currentPhase = PHASE_BID;
    trump = SUIT_UNDEFINED;
}

void GameController::bid(int bidAmount)
{
    playerArr[PLAYER_1].bid = bidAmount;
    currentBid = bidAmount;

    vector<int> playerNumArr = {PLAYER_2, PLAYER_3, PLAYER_4}; // cpu players

    for (auto playerNum : playerNumArr)
    {
        playerArr[playerNum].bid = cpu.getBid(playerNum);

        if (playerArr[playerNum].bid > currentBid)
        {
            currentBid = playerArr[playerNum].bid;
        }
    }

    if (getNumPassed() == 3)
    {
        winningBidder = PLAYER_1;
        currentPhase = PHASE_MIDDLE;
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
            if (playerArr[playerNum].bid == 0 || playerArr[playerNum].bid != currentBid)
            {
                playerArr[playerNum].bid = cpu.getBid(playerNum);
            }

            if (playerArr[playerNum].bid > currentBid)
            {
                currentBid = playerArr[playerNum].bid;
            }
        }
    }

    for (auto &player : playerArr)
    {
        if (player.bid != 0)
        {
            winningBidder = player.playerNum;
            currentPhase = PHASE_MIDDLE;
            return;
        }
    }
}

void GameController::startGame()
{
    currentPhase = PHASE_PLAY;

    // todo
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

void GameController::incrementPlayerNum(int &playerNum)
{
    switch (playerNum)
    {
    case PLAYER_1:
        playerNum = PLAYER_2;
        return;
    case PLAYER_2:
        playerNum = PLAYER_3;
        return;
    case PLAYER_3:
        playerNum = PLAYER_4;
        return;
    case PLAYER_4:
        playerNum = PLAYER_1;
        return;
    default:
        playerNum = PLAYER_UNDEFINED;
        return;
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
        incrementPlayerNum(playerNum);
    }

    while (deck.size() > 0)
    {
        Card currentCard = deck.back(); // copy
        deck.pop_back();

        nest.push_back(currentCard);
    }

    sortCardArray(nest);
    sortCardArray(playerArr[PLAYER_1].cardArr);
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