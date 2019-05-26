#include "player.h"

Player::Player(int pPlayerNum)
{
    playerNum = pPlayerNum;
    teamNum = TEAM_UNDEFINED;
    cardArr.clear();
    bid = 0;
}

string Player::getPlayerName()
{
    switch (playerNum)
    {
    case PLAYER_1:
        return "Player 1";
    case PLAYER_2:
        return "Player 2";
    case PLAYER_3:
        return "Player 3";
    case PLAYER_4:
        return "Player 4";
    default:
        return "???"; // not implemented
    }
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