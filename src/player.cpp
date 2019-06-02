#include "player.h"

Player::Player(int pPlayerNum, string pPlayerName)
{
    playerNum = pPlayerNum;
    playerName = pPlayerName;
    teamNum = TEAM_UNDEFINED;
    cardArr.clear();
    bid = 0;
}

int Player::getNextPlayerNum()
{
    switch (playerNum)
    {
    case PLAYER_1:
        return PLAYER_2;
    case PLAYER_2:
        return PLAYER_3;
    case PLAYER_3:
        return PLAYER_4;
    case PLAYER_4:
        return PLAYER_1;
    default:
        return PLAYER_UNDEFINED;
    }
}