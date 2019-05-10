#include "cpuPlayer.h"
#include "gameController.h"

#include <map>

double phi(double x)
{
    // constants
    double a1 = 0.254829592;
    double a2 = -0.284496736;
    double a3 = 1.421413741;
    double a4 = -1.453152027;
    double a5 = 1.061405429;
    double p = 0.3275911;

    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x) / sqrt(2.0);

    // A&S formula 7.1.26
    double t = 1.0 / (1.0 + p * x);
    double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

    return 0.5 * (1.0 + sign * y);
}

CpuPlayer::CpuPlayer()
{
}

int CpuPlayer::getBid(int playerNum)
{
    vector<Card> &cards = gc.playerArr[playerNum].cardArr;

    sortCardArray(cards);

    double totalValue = 0.0;

    for (auto &card : cards)
    {
        totalValue += card.value;
    }

    double averageValue = totalValue / cards.size();

    const double MU = 7.54;
    const double SIGMA = 0.987;

    double P = phi((averageValue - MU) / SIGMA); // percentile

    map<double, int> bidMap{
        make_pair(0.1, 50), make_pair(0.2, 55), make_pair(0.3, 60), make_pair(0.4, 65),
        make_pair(0.5, 70), make_pair(0.6, 75), make_pair(0.7, 80), make_pair(0.8, 85),
        make_pair(0.9, 90)};

    auto It = bidMap.upper_bound(P);
    auto maxBid = It != bidMap.end() ? It->second : 95;
    
    int bid = maxBid > gc.currentBid ? gc.currentBid + 5 : 0;

    return bid;
}