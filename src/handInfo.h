#ifndef HANDINFO_H
#define HANDINFO_H

#include <map>

#include "card.h"

using namespace std;

// forward declarations
class GameController;

// global declarations
extern GameController gc;

struct HandInfo
{
    map<int /*PLAYER_NUM*/, Card> cardPlayed;

    int suit; // suit for current hand

    int points;

    HandInfo();
    void clear();

    pair<Card, int /*PLAYER_NUM*/> getWinningPair(); // return PLAYER_NUM which won hand
};

#endif