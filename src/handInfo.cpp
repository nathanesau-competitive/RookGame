#include "gameController.h"
#include "handInfo.h"

HandInfo::HandInfo()
{
    clear();
}

void HandInfo::clear()
{
    cardPlayed.clear();
    points = 0;
    suit = SUIT_UNDEFINED;
}

pair<Card, int> HandInfo::getWinningPair()
{
    int trump = gc.trump;

    pair<Card, int> winningPair = make_pair(cardPlayed[PLAYER_1], PLAYER_1);

    vector<int> playerNumArr = {PLAYER_2, PLAYER_3, PLAYER_4}; // cpu players

    for (auto playerNum : playerNumArr)
    {
        pair<Card, int> currentPair = make_pair(cardPlayed[playerNum], playerNum);

        if(currentPair.first.suit == winningPair.first.suit)
        {
            if(currentPair.first.value > winningPair.first.value)
            {
                winningPair = currentPair;
            }
        }
        else // not the same suit
        {
            if(currentPair.first.suit == trump)
            {
                winningPair = currentPair;
            }
        }
    }

    return winningPair;
}
