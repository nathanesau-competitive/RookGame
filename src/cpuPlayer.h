#ifndef CPUPLAYER_H
#define CPUPLAYER_H

#include "card.h"

// forward declarations
class GameController;

// global declarations
extern GameController gc;

// uses information in GameController to determine CPU actions
class CpuPlayer
{
public:
    CpuPlayer();

    int getBid(int playerNum); // return 0 if passing

    Card getCardToPlay(int playerNum);
};

#endif