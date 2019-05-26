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
#include "overallInfo.h"
#include "player.h"
#include "roundInfo.h"

using namespace std;

// forward declarations
class CpuPlayer;

// global declarations
extern CpuPlayer cpu;

class GameController
{
public:
    OverallInfo overallInfo;
    RoundInfo roundInfo;
    HandInfo handInfo;

    CardVector deck;
    CardVector nest;
    vector<Player> playerArr;

public:
    GameController();

    void clear();

    // todo: improve names of these functions
    void onNewGame();
    void onBid(int pBidAmount);
    void onPass();

    void onStartGame();

    void playCard(Card cardPlayed, int playerNum);

    bool isRoundOver();

private:
    void initializeDeck();
    void dealDeck();

    int getNumPassed();
};

#endif