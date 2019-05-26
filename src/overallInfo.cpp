#include "overallInfo.h"
#include "roundInfo.h"

OverallInfo::OverallInfo()
{
    clear();
}

void OverallInfo::clear()
{
    playerScores.clear();
}

void OverallInfo::updatePlayerScores(RoundInfo &roundInfo)
{
    map<int, int> roundScores = roundInfo.getRoundScores();

    for (auto playerNum : vector<int>{PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4})
    {
        playerScores[playerNum] += roundScores[playerNum];
    }
}
