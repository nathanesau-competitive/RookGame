#ifndef GAMEINFOWIDGET_H
#define GAMEINFOWIDGET_H

#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <set>

#include "clickableCard.h"
#include "common.h"
#include "player.h"

// forward declarations
class GameController;

// global declarations
extern GameController gc;

struct GameInfoWidget : public QDialogWithClickableCardArray
{
    QMainWindow *mainWindow;

    ScaledQLabel bidCategoryLabel;
    ScaledQLabel bidPlayerLabel;
    ScaledQLabel bidAmountLabel;

    ScaledQLabel partnerCardCategoryLabel;
    ClickableCardArray topLeftCards;

    ScaledQLabel trumpCategoryLabel;
    ScaledQLabel trumpLabel;

    ScaledQLabel pointsMiddleCategoryLabel;
    ScaledQLabel pointsMiddleLabel;

    ScaledQLabel teamsCategoryLabel;
    ScaledQLabel team1Label;
    ScaledQLabel team2Label;

    ScaledQLabel pointsWonPlayerCategoryLabel;
    ScaledQLabel pointsWonPlayerLabel1;
    ScaledQLabel pointsWonPlayerLabel2;
    ScaledQLabel pointsWonPlayerLabel3;
    ScaledQLabel pointsWonPlayerLabel4;

    ScaledQLabel pointsWonTeamCategoryLabel;
    ScaledQLabel pointsWonTeamLabel1;
    ScaledQLabel pointsWonTeamLabel2;

    ScaledQLabel overallScoresCategoryLabel;
    ScaledQLabel player1OverallScoreLabel;
    ScaledQLabel player2OverallScoreLabel;
    ScaledQLabel player3OverallScoreLabel;
    ScaledQLabel player4OverallScoreLabel;

    GameInfoWidget(QMainWindow *pMainWindow, QWidget *parent = nullptr);

    void resetInfoToDefaults();

    virtual void onCardClicked(ClickableCard *clickableCard)
    {
        // do nothing
    }

    virtual void onCardHoverEnter(ClickableCard *clickableCard);
    virtual void onCardHoverLeave(ClickableCard *clickableCard);

    void updateBid(int playerNum, int amount, bool showBlankAmount = false);
    void updatePartner(Card partnerCard, int playerNum = PLAYER_UNDEFINED);
    void updateTrump(int trumpSuit);
    void updatePointsMiddle(int pointsMiddle, bool showBlank = false);
    void updateTeam1(set<int> team1);
    void updateTeam2(set<int> team2);
    void updatePoints(map<int, int> playerScores, map<int, int> teamScores, pair<set<int>, set<int>> teams);
    void updateOverallScores(int player1Score, int player2Score, int player3Score, int player4Score);
};

#endif