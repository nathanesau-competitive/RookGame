#ifndef CPUPLAYER_H
#define CPUPLAYER_H

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class CpuPlayer
{
public:

    CpuPlayer();

    int getBid(int playerNum); // return 0 if passing
};

#endif