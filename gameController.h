#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <assert.h>

using namespace std;

// forward declarations
class CpuPlayer;
class MainWindow;

// global declarations
extern CpuPlayer cpu;

// DO NOT MODIFY
const int PLAYER_UNDEFINED = -1;
const int PLAYER_1 = 0;
const int PLAYER_2 = 1;
const int PLAYER_3 = 2;
const int PLAYER_4 = 3;

// DO NOT MODIFY
const int SUIT_UNDEFINED = -1;
const int SUIT_BLACK = 0;
const int SUIT_GREEN = 1;
const int SUIT_RED = 2;
const int SUIT_YELLOW = 3;
const int SUIT_SPECIAL = 4;

// DO NOT MODIFY
const int PHASE_UNDEFINED = -1;
const int PHASE_BID = 0;
const int PHASE_MIDDLE = 1;
const int PHASE_PLAY = 2;

// DO NOT MODIFY
const int VALUE_UNDEFINED = -1;
const int VALUE_ROOK = 0;
const int VALUE_1 = 1;
const int VALUE_2 = 2;
const int VALUE_3 = 3;
const int VALUE_4 = 4;
const int VALUE_5 = 5;
const int VALUE_6 = 6;
const int VALUE_7 = 7;
const int VALUE_8 = 8;
const int VALUE_9 = 9;
const int VALUE_10 = 10;
const int VALUE_11 = 11;
const int VALUE_12 = 12;
const int VALUE_13 = 13;
const int VALUE_14 = 14;

struct Card
{
    int suit = SUIT_UNDEFINED;
    int value = VALUE_UNDEFINED;

    Card(int pSuit = SUIT_UNDEFINED, int pValue = VALUE_UNDEFINED);
    bool operator==(const Card &p);

    int getPointValue();
};

struct Player
{
    const int playerNum;
    vector<Card> cardArr;

    int bid;

    Player(const int pPlayerNum);
};

struct SuitInfo
{
    int suit = SUIT_UNDEFINED;
    int count = 0;
    int totalValue = 0;

    SuitInfo(int pSuit, int pCount = 0, int pTotalValue = 0) : suit(pSuit), count(pCount), totalValue(pTotalValue)
    {
    }

    bool operator==(const SuitInfo &p)
    {
        return p.suit == suit;
    }
};

// global functions
void sortCardArray(vector<Card> &cardArr);
vector<SuitInfo> getSuitInfoArr(vector<Card> &cardArr);

class GameController
{
public:
    MainWindow *mw;

    int currentTurn;   // whose turn, i.e. PLAYER_1
    int currentBid;    // maximum bid, i.e. 80
    int winningBidder; // who won the bid, i.e. PLAYER_1
    int currentPhase;  // PHASE_BID, PHASE_MIDDLE, PHASE_PLAY
    int trump;         // trump for this round, i.e. SUIT_BLACK

    vector<Card> deck;
    vector<Player> playerArr;
    vector<Card> nest;

    GameController();

    void clear();

    void newGame();          // corresponds to "File->New Game"
    void bid(int bidAmount); // corresponds to "Bid Dialog->Bid"
    void pass();             // corresponds to "Bid Dialog->Pass"
    void startGame();

private:
    void initializeDeck();
    void initializePlayerArr();
    void incrementPlayerNum(int &playerNum);
    void dealDeck();

    // bidding phase
    int getNumPassed();
};

#endif