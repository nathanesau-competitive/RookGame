#include "cpuPlayer.h"
#include "gameController.h"
#include "utils.h"

#include <map>
#include <vector>

using namespace std;

CpuPlayer::CpuPlayer()
{
}

int CpuPlayer::getBid(int playerNum)
{
    vector<Card> &cardArr = gc.playerArr[playerNum].cardArr;

    Utils::Game::sortCardArray(cardArr);

    double totalValue = 0.0;

    for (auto &card : cardArr)
    {
        totalValue += card.value;
    }

    double averageValue = totalValue / cardArr.size();

    const double MU = 7.54;
    const double SIGMA = 0.987;

    double P = Utils::Stat::phi((averageValue - MU) / SIGMA); // percentile

    map<double, int> bidMap{
        make_pair(0.1, 50), make_pair(0.2, 55), make_pair(0.3, 60), make_pair(0.4, 65),
        make_pair(0.5, 70), make_pair(0.6, 75), make_pair(0.7, 80), make_pair(0.8, 85),
        make_pair(0.9, 90)};

    auto It = bidMap.upper_bound(P);
    auto maxBid = It != bidMap.end() ? It->second : 95;

    int bid = maxBid > gc.bidAmount ? gc.bidAmount + 5 : 0;

    return bid;
}

Card CpuPlayer::getCardToPlay(int playerNum)
{
    vector<Card> &cardArr = gc.playerArr[playerNum].cardArr;

    vector<Card> playableCards = Utils::Game::getPlayableCards(cardArr);

    Card bestCard = Utils::Game::getBestCard(playableCards);

    return bestCard;
}