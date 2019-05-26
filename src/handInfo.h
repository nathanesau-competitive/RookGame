#ifndef HANDINFO_H
#define HANDINFO_H

#include <map>

#include "card.h"
#include "player.h"

using namespace std;

// forward declarations
class RoundInfo;

class HandInfo
{
    const RoundInfo &roundInfo;

    Card winningCard;
    int winningPlayerNum;

public:
    int startingPlayerNum;

    map<int /*playerNum*/, Card> cardPlayed;
    int suit;
    int points;

public:
    HandInfo(const RoundInfo &pRoundInfo);
    void clear();

    int getWinningPlayerNum();
    Card getWinningCard();

private:
    void updateWinningCombination();
};

#endif