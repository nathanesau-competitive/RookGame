#ifndef GAMEMENUWIDGET_H
#define GAMEMENUWIDGET_H

#include "common.h"

// forward declarations
class MainWindow;

class GameMenuWidget : public ScaledQDialog
{
    MainWindow *mainWindow;

    ScaledQLabel *menuTitleLabel;
    ScaledQPushButton *newGameButton;
    ScaledQPushButton *newRoundButton;
    ScaledQPushButton *saveGameButton;
    ScaledQPushButton *loadGameButton;
    ScaledQPushButton *quitGameButton;

public:
    GameMenuWidget(MainWindow *pMainWindow, QWidget *parent = nullptr);
    void rescale();

    void onNewGameButtonPressed();
    void onNewRoundButtonPressed();
    void onSaveGameButtonPressed();
    void onLoadGameButtonPressed();
    void onQuitGameButtonPressed();
};

#endif