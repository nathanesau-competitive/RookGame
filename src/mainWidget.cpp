#include <QThread>
#include <set>
#include <string>

#include "cpuPlayer.h"
#include "gameController.h"
#include "mainWidget.h"
#include "mainWindow.h"
#include "roundSummaryDialog.h"
#include "utils.h"

using namespace std;

MainWidget::MainWidget(MainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                   QDialogWithClickableCardArray(false, parent)
{
    auto setupLabel = [this](QLabel *label, QString text, QPoint pos, QSize size) {
        label->setParent(this);
        label->setFont(QFont("Times", 11));
        label->setText(text);
        label->move(pos);
        label->resize(size);
        label->setStyleSheet("background-color: white");
        label->setAlignment(Qt::AlignCenter);
    };

    centerCards = new ClickableCardArray(DRAW_POSITION_MAIN_WIDGET_CENTER, SIZE_NORMAL, this);
    bottomCards = new ClickableCardArray(DRAW_POSITION_MAIN_WIDGET_BOTTOM, SIZE_NORMAL, this);
    
    player1CardPlayed = new ClickableCardArray(DRAW_POSITION_MAIN_WIDGET_CENTER_BOTTOM, SIZE_NORMAL, this);
    player2CardPlayed = new ClickableCardArray(DRAW_POSITION_MAIN_WIDGET_CENTER_LEFT, SIZE_NORMAL, this);
    player3CardPlayed = new ClickableCardArray(DRAW_POSITION_MAIN_WIDGET_CENTER_TOP, SIZE_NORMAL, this);
    player4CardPlayed = new ClickableCardArray(DRAW_POSITION_MAIN_WIDGET_CENTER_RIGHT, SIZE_NORMAL, this);

    map<int, string> playerNames = Utils::Db::readPlayerNamesFromDb();

    player1NameLabel = new ScaledQLabel;
    setupLabel(player1NameLabel, QString::fromStdString(playerNames[PLAYER_1]), {550, 800}, {75, 25});

    player2NameLabel = new ScaledQLabel;
    setupLabel(player2NameLabel, QString::fromStdString(playerNames[PLAYER_2]), {25, 425}, {75, 25});

    player3NameLabel = new ScaledQLabel;
    setupLabel(player3NameLabel, QString::fromStdString(playerNames[PLAYER_3]), {550, 140}, {75, 25});

    player4NameLabel = new ScaledQLabel;
    setupLabel(player4NameLabel, QString::fromStdString(playerNames[PLAYER_4]), {1100, 425}, {75, 25});

    updateNameTags(Utils::Db::readShowNameTagsFromDb());

    infoWidget = new GameInfoWidget(pMainWindow);
    infoWidget->setParent(this);
    infoWidget->move(QPoint(0, 0));
    infoWidget->resize(1200, 130);

    menuWidget = new GameMenuWidget(pMainWindow);
    menuWidget->setParent(this);
    menuWidget->move(QPoint(400, 300));
    menuWidget->resize(400, 300);

    // no window title, etc.
}

void MainWidget::rescale()
{
    updateScaleFactor();
    setGeometry(geometry());

    for (auto clickableCardArray : vector<ClickableCardArray *>{player1CardPlayed, player2CardPlayed,
                                                                player3CardPlayed, player4CardPlayed,
                                                                centerCards, bottomCards})
        clickableCardArray->rescale();

    for (auto label : vector<ScaledQLabel *>{player1NameLabel, player2NameLabel,
                                             player3NameLabel, player4NameLabel})
        label->rescale();

    for (auto widget : vector<GameInfoWidget *>{infoWidget})
        widget->rescale();

    for (auto widget : vector<GameMenuWidget *>{menuWidget})
        widget->rescale();
}

void MainWidget::finishExistingHand(Card player1Card)
{
    gc.playCard(player1Card, PLAYER_1);

    bottomCards->showCards(gc.playerArr[PLAYER_1].cardArr);

    showCardPlayed(player1Card, PLAYER_1);

    for (auto playerNum : vector<int>{PLAYER_2, PLAYER_3, PLAYER_4})
    {
        if (gc.handInfo.cardPlayed[playerNum] == Card(SUIT_UNDEFINED, VALUE_UNDEFINED)) // cpu hasn't played yet
        {
            gc.playCard(cpu.getCardToPlay(playerNum), playerNum);

            showCardPlayed(gc.handInfo.cardPlayed[playerNum], playerNum);
        }
    }

    gc.roundInfo.updateScores(gc.handInfo);

    showPartnerCardIfApplicable();

    infoWidget->updatePlayerPoints(gc.roundInfo.playerScores);
    infoWidget->updateTeamPoints(gc.roundInfo.teamScores);

    showHandResult();

    player1CardPlayed->hideCards();
    player2CardPlayed->hideCards();
    player3CardPlayed->hideCards();
    player4CardPlayed->hideCards();
}

void MainWidget::startNewHand(int startingPlayerNum)
{
    if (startingPlayerNum != PLAYER_1)
    {
        // sleep before starting hand
        repaint();
        QThread::msleep(500);
    }

    gc.handInfo.clear();

    int playerNum = startingPlayerNum;

    while (playerNum != PLAYER_1)
    {
        gc.playCard(cpu.getCardToPlay(playerNum), playerNum);

        showCardPlayed(gc.handInfo.cardPlayed[playerNum], playerNum);

        playerNum = gc.playerArr[playerNum].getNextPlayerNum();
    }

    // wait for card click to finish hand
}

bool MainWidget::validateCard(ClickableCard *clickableCard)
{
    CardVector playableCards = gc.playerArr[PLAYER_1].cardArr.getPlayableCards(gc.handInfo);

    if (std::find(playableCards.begin(), playableCards.end(), clickableCard->data) == playableCards.end()) // invalid card
    {
        MessageBox msgBox;
        msgBox.showCards({clickableCard->data});
        Utils::Ui::setupMessageBox(&msgBox, "Invalid card clicked. Must follow suit.", "Invalid card");
        Utils::Ui::moveDialog(&msgBox, mainWindow, DIALOG_POSITION_CENTER);
        msgBox.exec();

        return false;
    }

    return true;
}

void MainWidget::onCardClicked(ClickableCard *clickableCard)
{
    if (!validateCard(clickableCard))
    {
        return;
    }

    finishExistingHand(clickableCard->data);

    if (gc.isRoundOver())
    {
        gc.roundInfo.addPointsMiddleToScores(gc.handInfo);

        centerCards->showCards(gc.nest);

        infoWidget->updatePlayerPoints(gc.roundInfo.playerScores);
        infoWidget->updateTeamPoints(gc.roundInfo.teamScores);

        showNestResult();

        centerCards->hideCards();

        gc.overallInfo.updatePlayerScores(gc.roundInfo);

        infoWidget->updateOverallScores(gc.overallInfo.playerScores);

        RoundSummaryDialog summaryDlg;
        summaryDlg.updateScores(gc.roundInfo.getRoundScores());
        Utils::Ui::moveDialog(&summaryDlg, mainWindow, DIALOG_POSITION_CENTER);

        if (!summaryDlg.exec())
        {
            qFatal("Problem executing round summary dialog");
            return;
        }

        // show game menu
        menuWidget->show();
    }
    else
    {
        startNewHand(gc.handInfo.getWinningPlayerNum());
    }
}

void MainWidget::onCardHoverEnter(ClickableCard *clickableCard)
{
    // do nothing
}

void MainWidget::onCardHoverLeave(ClickableCard *clickableCard)
{
    // do nothing
}

void MainWidget::showCardPlayed(const Card &card, int playerNum)
{
    switch (playerNum)
    {
    case PLAYER_1:
        player1CardPlayed->showCards({card});
        break;
    case PLAYER_2:
        player2CardPlayed->showCards({card});
        break;
    case PLAYER_3:
        player3CardPlayed->showCards({card});
        break;
    case PLAYER_4:
        player4CardPlayed->showCards({card});
        break;
    }

    bool sleep = []() {
        return true; // sleep after any card is played
    }();

    if (sleep)
    {
        repaint();
        QThread::msleep(500);
    }
}

void MainWidget::showPartnerCardIfApplicable()
{
    for (auto it = gc.handInfo.cardPlayed.begin(); it != gc.handInfo.cardPlayed.end(); it++)
    {
        auto currentCard = (*it).second;

        if (currentCard == gc.roundInfo.partnerCard)
        {
            infoWidget->updatePartner(currentCard, gc.roundInfo.partnerPlayerNum);
            infoWidget->updateTeam1(gc.roundInfo.teams.first);
            infoWidget->updateTeam2(gc.roundInfo.teams.second);

            string msg = gc.playerArr[gc.roundInfo.partnerPlayerNum].playerName + " is the partner. Teams updated.";

            MessageBox msgBox;
            msgBox.showCards({gc.roundInfo.partnerCard});
            Utils::Ui::setupMessageBox(&msgBox, QString::fromStdString(msg), "Partner card", {325, 250});
            Utils::Ui::moveDialog(&msgBox, mainWindow, DIALOG_POSITION_CENTER);
            msgBox.exec();

            return;
        }
    }
}

void MainWidget::showHandResult()
{
    auto msg = []() -> string {
        return gc.playerArr[gc.handInfo.getWinningPlayerNum()].playerName +
               " won the hand for " + to_string(gc.handInfo.points) + " points with the";
    }();

    MessageBox msgBox;
    msgBox.showCards({gc.handInfo.getWinningCard()});
    Utils::Ui::setupMessageBox(&msgBox, QString::fromStdString(msg), "Hand result", {340, 250});
    Utils::Ui::moveDialog(&msgBox, mainWindow, DIALOG_POSITION_CENTER);
    msgBox.exec();
}

void MainWidget::showNestResult()
{
    string msg = gc.playerArr[gc.handInfo.getWinningPlayerNum()].playerName +
                 " won the nest. Nest had " + to_string(gc.roundInfo.pointsMiddle) + " points.";

    MessageBox msgBox;
    Utils::Ui::setupMessageBox(&msgBox, QString::fromStdString(msg), "Last hand");
    Utils::Ui::moveDialog(&msgBox, mainWindow, DIALOG_POSITION_CENTER);
    msgBox.exec();
}

void MainWidget::updateNameTags(bool showNameTags)
{
    if (showNameTags)
    {
        player1NameLabel->show();
        player2NameLabel->show();
        player3NameLabel->show();
        player4NameLabel->show();
    }
    else
    {
        player1NameLabel->hide();
        player2NameLabel->hide();
        player3NameLabel->hide();
        player4NameLabel->hide();
    }
}