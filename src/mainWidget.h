#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "clickableCard.h"
#include "common.h"
#include "gameInfoWidget.h"
#include "gameMenuWidget.h"

// forward declarations
class CpuPlayer;
class GameController;
class MainWindow;

// global declarations
extern CpuPlayer cpu;
extern GameController gc;

class MainWidget : public QDialogWithClickableCardArray
{
    MainWindow *mainWindow; // non-owning

public:
    GameInfoWidget *infoWidget;
    GameMenuWidget *menuWidget;

    ScaledQLabel *player1NameLabel;
    ClickableCardArray *player1CardPlayed;

    ScaledQLabel *player2NameLabel;
    ClickableCardArray *player2CardPlayed;

    ScaledQLabel *player3NameLabel;
    ClickableCardArray *player3CardPlayed;

    ScaledQLabel *player4NameLabel;
    ClickableCardArray *player4CardPlayed;

    ClickableCardArray *centerCards;
    ClickableCardArray *bottomCards;

    MainWidget(MainWindow *pMainWindow, QWidget *parent = nullptr);
    virtual void rescale();

    virtual void onCardClicked(ClickableCard *clickableCard);
    virtual void onCardHoverEnter(ClickableCard *clickableCard);
    virtual void onCardHoverLeave(ClickableCard *clickableCard);

    bool validateCard(ClickableCard *clickableCard); // return true if valid

    void finishExistingHand(Card player1Card); // intentional copy
    void startNewHand(int startingPlayerNum);

    void showCardPlayed(const Card &card, int playerNum);

    void showPartnerCardIfApplicable();
    void showHandResult();
    void showNestResult();

    // appearance dialog
    void updateNameTags(bool showNameTags);
};

#endif