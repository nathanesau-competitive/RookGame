#include <set>
#include <QThread>

#include "gameController.h"
#include "mainWidget.h"
#include "roundSummaryDialog.h"
#include "utils.h"

MainWidget::MainWidget(QMainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                    infoWidget(pMainWindow),
                                                                    QDialogWithClickableCardArray(parent),
                                                                    bottomCards(DRAW_POSITION_MAIN_WIDGET_BOTTOM, SIZE_NORMAL, this),
                                                                    player1CardPlayed(DRAW_POSITION_MAIN_WIDGET_CENTER_BOTTOM, SIZE_NORMAL, this),
                                                                    player2CardPlayed(DRAW_POSITION_MAIN_WIDGET_CENTER_LEFT, SIZE_NORMAL, this),
                                                                    player3CardPlayed(DRAW_POSITION_MAIN_WIDGET_CENTER_TOP, SIZE_NORMAL, this),
                                                                    player4CardPlayed(DRAW_POSITION_MAIN_WIDGET_CENTER_RIGHT, SIZE_NORMAL, this)
{
    infoWidget.setParent(this);
    infoWidget.move(QPoint(0, 0));
    infoWidget.resize(1200, 130);
}

void MainWidget::onCardClicked(ClickableCard *clickableCard)
{
    // todo: MAKE sure it is a card in player 1's hand otherwise don't do anything (i.e. ignore click on played cards)

    Card card = clickableCard->data;

    gc.playHand(card);

    showBottomCards(gc.playerArr[PLAYER_1].cardArr);

    showCardPlayed(card, PLAYER_1, true);
    showCardPlayed(gc.handInfo.cardPlayed[PLAYER_2], PLAYER_2, true);
    showCardPlayed(gc.handInfo.cardPlayed[PLAYER_3], PLAYER_3, true);
    showCardPlayed(gc.handInfo.cardPlayed[PLAYER_4], PLAYER_4, false);

    for (auto it = gc.handInfo.cardPlayed.begin(); it != gc.handInfo.cardPlayed.end(); it++)
    {
        auto currentCard = (*it).second;

        if (currentCard == gc.partnerPair.first)
        {
            gc.partnerPair.second = (*it).first;
            infoWidget.updatePartner(currentCard, gc.partnerPair.second);

            // todo: make determining teams a Utils::Game function
            auto &team1 = gc.teams.first;
            team1.insert(gc.bidPlayer);
            team1.insert(gc.partnerPair.second);

            auto &team2 = gc.teams.second;
            vector<int> playerNumArr = {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4};

            for (auto playerNum : playerNumArr)
            {
                if (team1.find(playerNum) == team1.end())
                {
                    team2.insert(playerNum);
                }
            }

            infoWidget.updateTeam1(team1);
            infoWidget.updateTeam2(team2);

            string msg = Utils::Ui::getPlayerName(gc.partnerPair.second) + " is the partner. Teams updated.";

            MessageBox msgBox;
            msgBox.showCards({gc.partnerPair.first});
            Utils::Ui::setupMessageBox(&msgBox, QString::fromStdString(msg), "Partner card", {250, 250});
            Utils::Ui::moveDialog(&msgBox, mainWindow, DIALOG_POSITION_CARD_MESSAGE_BOX);
            msgBox.exec();
        }
    }

    if(!gc.teams.first.empty() && !gc.teams.second.empty()) // teams known
    {
        gc.teamScores[TEAM_1] = 0;
        for(auto It = gc.teams.first.begin(); It != gc.teams.first.end(); It++)
        {
            int playerNum = (*It);
            gc.teamScores[TEAM_1] += gc.playerScores[playerNum];
        }

        gc.teamScores[TEAM_2] = 0;
        for(auto It = gc.teams.second.begin(); It != gc.teams.second.end(); It++)
        {
            int playerNum = (*It);
            gc.teamScores[TEAM_2] += gc.playerScores[playerNum];
        }
    }

    infoWidget.updatePoints(gc.playerScores, gc.teamScores, gc.teams);

    auto msg = []() -> string {
        auto winningPair = gc.handInfo.getWinningPair();
        return Utils::Ui::getPlayerName(winningPair.second) +
               " won the hand for " + to_string(gc.handInfo.points) + " points with the";
    }();

    if (!msg.empty())
    {
        MessageBox msgBox;
        msgBox.showCards({gc.handInfo.getWinningPair().first});
        Utils::Ui::setupMessageBox(&msgBox, QString::fromStdString(msg), "Hand result", {325, 250});
        Utils::Ui::moveDialog(&msgBox, mainWindow, DIALOG_POSITION_CARD_MESSAGE_BOX);
        msgBox.exec();
    }

    player1CardPlayed.hideCards();
    player2CardPlayed.hideCards();
    player3CardPlayed.hideCards();
    player4CardPlayed.hideCards();

    if (gc.playerArr[PLAYER_1].cardArr.empty())
    {
        MessageBox msgBox;

        string msg = Utils::Ui::getPlayerName(gc.handInfo.getWinningPair().second) +
            " won the nest for " + to_string(gc.pointsMiddle) + " points.";

        Utils::Ui::setupMessageBox(&msgBox, QString::fromStdString(msg), "Last hand");
        Utils::Ui::moveDialog(&msgBox, mainWindow, DIALOG_POSITION_CENTER);
        msgBox.exec();

        // show round summary dialog
        auto roundSummaryDlg = RoundSummaryDialog();
        Utils::Ui::moveDialog(&roundSummaryDlg, mainWindow, DIALOG_POSITION_CENTER);
        
        if(!roundSummaryDlg.exec())
        {
            qFatal("Problem executing round summary dialog");
            return;
        }
    }
}

void MainWidget::showCardPlayed(const Card &card, int playerNum, bool sleep)
{
    switch (playerNum)
    {
    case PLAYER_1:
        player1CardPlayed.showCards({card});
        break;
    case PLAYER_2:
        player2CardPlayed.showCards({card});
        break;
    case PLAYER_3:
        player3CardPlayed.showCards({card});
        break;
    case PLAYER_4:
        player4CardPlayed.showCards({card});
        break;
    }

    if (sleep)
    {
        repaint();
        QThread::msleep(500);
    }
}

void MainWidget::showBottomCards(const vector<Card> &cardArr)
{
    bottomCards.showCards(cardArr);
}
