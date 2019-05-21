#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>

#include "clickableCard.h"
#include "gameInfoWidget.h"

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class MainWidget : public QDialogWithClickableCardArray
{
    QMainWindow *mainWindow;

public:
    GameInfoWidget infoWidget;

    ClickableCardArray player1CardPlayed;
    ClickableCardArray player2CardPlayed;
    ClickableCardArray player3CardPlayed;
    ClickableCardArray player4CardPlayed;

    ClickableCardArray bottomCards;

    MainWidget(QMainWindow *pMainWindow, QWidget *parent = nullptr);

    virtual void onCardClicked(ClickableCard *clickableCard);

    virtual void onCardHoverEnter(ClickableCard *clickableCard)
    {
        // do nothing
    }

    virtual void onCardHoverLeave(ClickableCard *clickableCard)
    {
        // do nothing
    }

    void showCardPlayed(const Card &card, int playerNum, bool sleep = false);
    void showBottomCards(const vector<Card> &cardArr);
};

#endif