#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <set>

#include "card.h"

using namespace std;

// typedef declarations
typedef set<int> Team;

// DO NOT MODIFY
const int PLAYER_UNDEFINED = -1;
const int PLAYER_1 = 0;
const int PLAYER_2 = 1;
const int PLAYER_3 = 2;
const int PLAYER_4 = 3;

// DO NOT MODIFY
const int TEAM_UNDEFINED = -1;
const int TEAM_1 = 0;
const int TEAM_2 = 1;

struct Player
{
    int playerNum;
    string playerName;
    int teamNum;
    CardVector cardArr;

    int bid;

public:
    Player(int pPlayerNum, string pPlayerName);

    int getNextPlayerNum();
};

#endif