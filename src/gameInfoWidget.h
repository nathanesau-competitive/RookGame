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

struct ScoreCompare
{
    inline bool operator()(const pair<int, int> &score1, const pair<int, int> &score2)
    {
        if (score1.second < score2.second)
        {
            return false;
        }
        else if (score1.second == score2.second)
        {
            return score1.first < score2.first;
        }

        return true;
    }
};

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

    void resetRoundInfoToDefaults();
    void resetOverallInfoToDefaults();
    void resetInfoToDefaults();

    virtual void onCardClicked(ClickableCard *clickableCard)
    {
        // do nothing
    }

    virtual void onCardHoverEnter(ClickableCard *clickableCard);
    virtual void onCardHoverLeave(ClickableCard *clickableCard);

    void updateBid(int playerNum, int amount);
    void updatePartner(Card partnerCard, int playerNum = PLAYER_UNDEFINED);
    void updateTrump(int trumpSuit);
    void updatePointsMiddle(int pointsMiddle, bool showBlank = false);
    void updateTeam1(Team team1);
    void updateTeam2(Team team2);
    void updatePoints(map<int, int> playerScores, map<int, int> teamScores, pair<Team, Team> teams);
    void updateOverallScores(map<int, int> playerScores);

private:
    void updatePlayerPoints(map<int, int> playerScores);
    void updateTeamPoints(map<int, int> teamScores, pair<Team, Team> teams);

    string getTeamName(Team team);
};

#endif