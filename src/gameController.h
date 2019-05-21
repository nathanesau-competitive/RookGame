#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <algorithm>
#include <assert.h>
#include <chrono>
#include <map>
#include <random>
#include <set>
#include <vector>

#include "card.h"
#include "handInfo.h"
#include "player.h"

using namespace std;

// forward declarations
class CpuPlayer;

// global declarations
extern CpuPlayer cpu;

// DO NOT MODIFY
const int PHASE_UNDEFINED = -1;
const int PHASE_BID = 0;
const int PHASE_MIDDLE = 1;
const int PHASE_PLAY = 2;

class GameController
{
public:
    int currentTurn;
    int bidPlayer;
    int bidAmount;
    int phase;
    int trump;
    int pointsMiddle;
    pair<Card, int> partnerPair;
    HandInfo handInfo;
    pair<set<int>, set<int>> teams;
    map<int /*PLAYER_NUM*/, int> playerScores;
    map<int /*TEAM_NUM*/, int> teamScores;

    vector<Card> deck;
    vector<Player> playerArr;
    vector<Card> nest;

public:
    GameController();

    void clear();

    void newGame();          // corresponds to "File->New Game"
    void bid(int pBidAmount); // corresponds to "Bid Dialog->Bid"
    void pass();             // corresponds to "Bid Dialog->Pass"
    void startGame();

    // todo
    void playHand(Card cardPlayed);

private:
    void initializeDeck();
    void initializePlayerArr();
    void dealDeck();

    // bidding phase
    int getNumPassed();
};

#endif