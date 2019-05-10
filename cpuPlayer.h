#ifndef CPUPLAYER_H
#define CPUPLAYER_H

// forward declarations
struct Card;
class GameController;

// global declarations
extern GameController gc;

namespace Utils
{
namespace Stat
{
double phi(double x); // standard normal distribution cdf
}
}

// uses information in GameController to determine CPU actions
class CpuPlayer
{
public:

    CpuPlayer();

    int getBid(int playerNum); // return 0 if passing

    Card getCardToPlay(int playerNum);
};

#endif