#ifndef GAMEINFOWIDGET_H
#define GAMEINFOWIDGET_H

#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <set>

#include "clickableCard.h"
#include "player.h"

// forward declarations
class GameController;

// global declarations
extern GameController gc;

struct GameInfoWidget : public QDialogWithClickableCardArray
{
    QMainWindow *mainWindow;

    QLabel bidCategoryLabel;
    QLabel bidPlayerLabel;
    QLabel bidAmountLabel;

    QLabel partnerCardCategoryLabel;
    ClickableCardArray topLeftCards;

    QLabel trumpCategoryLabel;
    QLabel trumpLabel;

    QLabel pointsMiddleCategoryLabel;
    QLabel pointsMiddleLabel;

    QLabel teamsCategoryLabel;
    QLabel team1Label;
    QLabel team2Label;

    QLabel pointsWonPlayerCategoryLabel;
    QLabel pointsWonPlayerLabel1;
    QLabel pointsWonPlayerLabel2;
    QLabel pointsWonPlayerLabel3;
    QLabel pointsWonPlayerLabel4;

    QLabel pointsWonTeamCategoryLabel;
    QLabel pointsWonTeamLabel1;
    QLabel pointsWonTeamLabel2;

    QLabel overallScoresCategoryLabel;
    QLabel player1OverallScoreLabel;
    QLabel player2OverallScoreLabel;
    QLabel player3OverallScoreLabel;
    QLabel player4OverallScoreLabel;

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