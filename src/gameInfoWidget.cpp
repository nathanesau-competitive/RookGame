#include <QToolTip>

#include "card.h"
#include "gameController.h"
#include "gameInfoWidget.h"
#include "player.h"
#include "utils.h"

GameInfoWidget::GameInfoWidget(QMainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                            QDialogWithClickableCardArray(false, parent),
                                                                            topLeftCards(DRAW_POSITION_GAME_INFO_WIDGET, SIZE_TINY, this)
{
    auto setupCategoryLabel = [this](ScaledQLabel *categoryLabel, QString text, QSize size, QPoint pos) {
        categoryLabel->setParent(this);
        categoryLabel->setText(text);
        categoryLabel->setFont(QFont("Times", 12, QFont::Weight::Bold));
        categoryLabel->resize(size.width(), size.height());
        categoryLabel->move(pos);
    };

    auto setupLabel = [this](ScaledQLabel *label, QString text, QSize size, QPoint pos) {
        label->setParent(this);
        label->setText(text);
        label->setFont(QFont("Times", 10, QFont::Weight::Normal));
        label->resize(size.width(), size.height());
        label->move(pos);
    };

    setupCategoryLabel(&bidCategoryLabel, "Bid", {100, 20}, {25, 10});
    setupLabel(&bidPlayerLabel, "???", {100, 20}, {35, 35});
    setupLabel(&bidAmountLabel, "???", {100, 20}, {35, 55});

    setupCategoryLabel(&partnerCardCategoryLabel, "Partner", {100, 20}, {135, 10});

    setupCategoryLabel(&trumpCategoryLabel, "Trump", {100, 20}, {270, 10});
    setupLabel(&trumpLabel, "???", {50, 20}, {280, 35});
    trumpLabel.setAlignment(Qt::AlignHCenter);

    setupCategoryLabel(&pointsMiddleCategoryLabel, "Points Middle", {125, 20}, {380, 10});
    setupLabel(&pointsMiddleLabel, "???", {125, 20}, {390, 35});

    setupCategoryLabel(&teamsCategoryLabel, "Teams", {100, 20}, {530, 10});
    setupLabel(&team1Label, "???", {150, 20}, {540, 35});
    setupLabel(&team2Label, "???", {150, 20}, {540, 55});

    setupCategoryLabel(&pointsWonTeamCategoryLabel, "Points (by Team)", {150, 20}, {690, 10});
    setupLabel(&pointsWonTeamLabel1, "???", {150, 20}, {700, 35});
    setupLabel(&pointsWonTeamLabel2, "???", {150, 20}, {700, 55});

    setupCategoryLabel(&pointsWonPlayerCategoryLabel, "Points (by Player)", {150, 20}, {890, 10});
    setupLabel(&pointsWonPlayerLabel1, "Player 1: 0", {100, 20}, {900, 35});
    setupLabel(&pointsWonPlayerLabel2, "Player 2: 0", {100, 20}, {900, 55});
    setupLabel(&pointsWonPlayerLabel3, "Player 3: 0", {100, 20}, {900, 75});
    setupLabel(&pointsWonPlayerLabel4, "Player 4: 0", {100, 20}, {900, 95});

    setupCategoryLabel(&overallScoresCategoryLabel, "Scores", {100, 20}, {1080, 10});
    setupLabel(&player1OverallScoreLabel, "Player 1: 0", {100, 20}, {1090, 35});
    setupLabel(&player2OverallScoreLabel, "Player 2: 0", {100, 20}, {1090, 55});
    setupLabel(&player3OverallScoreLabel, "Player 3: 0", {100, 20}, {1090, 75});
    setupLabel(&player4OverallScoreLabel, "Player 4: 0", {100, 20}, {1090, 95});

    setStyleSheet("background-color: white");
}

void GameInfoWidget::rescale()
{
    updateScaleFactor();
    setGeometry(geometry());

    for (auto label : vector<ScaledQLabel *>{&bidCategoryLabel, &bidPlayerLabel, &bidAmountLabel, &partnerCardCategoryLabel,
                                             &trumpCategoryLabel, &trumpLabel, &pointsMiddleCategoryLabel, &pointsMiddleLabel,
                                             &teamsCategoryLabel, &team1Label, &team2Label, &pointsWonPlayerCategoryLabel,
                                             &pointsWonPlayerLabel1, &pointsWonPlayerLabel2, &pointsWonPlayerLabel3,
                                             &pointsWonPlayerLabel4, &pointsWonTeamCategoryLabel, &pointsWonTeamLabel1,
                                             &pointsWonTeamLabel2, &overallScoresCategoryLabel, &player1OverallScoreLabel,
                                             &player2OverallScoreLabel, &player3OverallScoreLabel, &player4OverallScoreLabel})
        label->rescale();

    for (auto clickableCardArray : vector<ClickableCardArray *>{&topLeftCards})
        clickableCardArray->rescale();
}

void GameInfoWidget::resetRoundInfoToDefaults()
{
    updateBid(PLAYER_UNDEFINED, 0);
    updatePoints(map<int, int>(), map<int, int>(), make_pair(Team(), Team()));
    updatePartner(Card());
    updateTrump(SUIT_UNDEFINED);
    updatePointsMiddle(0, true);
    updateTeam1({});
    updateTeam2({});
}

void GameInfoWidget::resetOverallInfoToDefaults()
{
    updateOverallScores(map<int, int>());
}

void GameInfoWidget::resetInfoToDefaults()
{
    resetRoundInfoToDefaults();
    resetOverallInfoToDefaults();
}

void GameInfoWidget::onCardClicked(ClickableCard *clickableCard)
{
    // do nothing
}

void GameInfoWidget::onCardHoverEnter(ClickableCard *clickableCard)
{
    auto toolTipText = [](int playerNum) -> QString {
        switch (playerNum)
        {
        case PLAYER_1:
            return "Player 1";
        case PLAYER_2:
            return "Player 2";
        case PLAYER_3:
            return "Player 3";
        case PLAYER_4:
            return "Player 4";
        default:
            return "???";
        }
    }(gc.roundInfo.partnerPlayerNum);

    QToolTip::showText(mainWindow->pos() + clickableCard->pos(), toolTipText, clickableCard);
}

void GameInfoWidget::onCardHoverLeave(ClickableCard *clickableCard)
{
    // do nothing
}

void GameInfoWidget::updateBid(int playerNum, int amount)
{
    if (playerNum == PLAYER_UNDEFINED) // bid round hasn't started yet
    {
        bidPlayerLabel.setText("???");
        bidAmountLabel.setText("???");
    }
    else
    {
        bidPlayerLabel.setText(QString::fromStdString(gc.playerArr[playerNum].getPlayerName()));
        bidAmountLabel.setText(QString::number(amount));
    }
}

void GameInfoWidget::updatePartner(Card partnerCard, int playerNum)
{
    topLeftCards.showCards({partnerCard});
}

void GameInfoWidget::updateTrump(int trumpSuit)
{
    switch (trumpSuit)
    {
    case SUIT_BLACK:
        trumpLabel.setStyleSheet("background-color: black; color: white");
        trumpLabel.setText("Black");
        break;
    case SUIT_GREEN:
        trumpLabel.setStyleSheet("background-color: green");
        trumpLabel.setText("Green");
        break;
    case SUIT_RED:
        trumpLabel.setStyleSheet("background-color: red");
        trumpLabel.setText("Red");
        break;
    case SUIT_YELLOW:
        trumpLabel.setStyleSheet("background-color: yellow");
        trumpLabel.setText("Yellow");
        break;
    default:
        trumpLabel.setStyleSheet("");
        trumpLabel.setText("???");
        break;
    }
}

void GameInfoWidget::updatePointsMiddle(int pointsMiddle, bool showBlank)
{
    if (showBlank)
    {
        pointsMiddleLabel.setText("???");
    }
    else
    {
        pointsMiddleLabel.setText(QString::number(pointsMiddle));
    }
}

void GameInfoWidget::updateTeam1(Team team1)
{
    if (team1.empty())
    {
        team1Label.setText("???");
    }
    else
    {
        team1Label.setText(QString::fromStdString(getTeamName(team1)));
    }
}

void GameInfoWidget::updateTeam2(Team team2)
{
    if (team2.empty())
    {
        team2Label.setText("???");
    }
    else
    {
        team2Label.setText(QString::fromStdString(getTeamName(team2)));
    }
}

void GameInfoWidget::updatePoints(map<int, int> playerScores, map<int, int> teamScores, pair<Team, Team> teams)
{
    updatePlayerPoints(playerScores);
    updateTeamPoints(teamScores, teams);
}

void GameInfoWidget::updateOverallScores(map<int, int> playerScores)
{
    auto setupLabel = [this](ScaledQLabel *label, int score, int playerNum) {
        string text = gc.playerArr[playerNum].getPlayerName() + ": " + to_string(score);
        label->setText(QString::fromStdString(text));
    };

    setupLabel(&player1OverallScoreLabel, playerScores[PLAYER_1], PLAYER_1);
    setupLabel(&player2OverallScoreLabel, playerScores[PLAYER_2], PLAYER_2);
    setupLabel(&player3OverallScoreLabel, playerScores[PLAYER_3], PLAYER_3);
    setupLabel(&player4OverallScoreLabel, playerScores[PLAYER_4], PLAYER_4);
}

void GameInfoWidget::updatePlayerPoints(map<int, int> playerScores)
{
    auto setupPointsPlayerLabel = [this](ScaledQLabel *label, int score, int playerNum) {
        string text = gc.playerArr[playerNum].getPlayerName() + ": " + to_string(score);
        label->setText(QString::fromStdString(text));
    };

    if (playerScores.empty())
    {
        setupPointsPlayerLabel(&pointsWonPlayerLabel1, 0, PLAYER_1);
        setupPointsPlayerLabel(&pointsWonPlayerLabel2, 0, PLAYER_2);
        setupPointsPlayerLabel(&pointsWonPlayerLabel3, 0, PLAYER_3);
        setupPointsPlayerLabel(&pointsWonPlayerLabel4, 0, PLAYER_4);
    }
    else
    {
        vector<pair<int, int>> sortedPlayerScores;

        for (auto It = playerScores.begin(); It != playerScores.end(); It++)
        {
            sortedPlayerScores.push_back(make_pair(It->first, It->second));
        }

        sort(sortedPlayerScores.begin(), sortedPlayerScores.end(), ScoreCompare());

        setupPointsPlayerLabel(&pointsWonPlayerLabel1, sortedPlayerScores[0].second, sortedPlayerScores[0].first);
        setupPointsPlayerLabel(&pointsWonPlayerLabel2, sortedPlayerScores[1].second, sortedPlayerScores[1].first);
        setupPointsPlayerLabel(&pointsWonPlayerLabel3, sortedPlayerScores[2].second, sortedPlayerScores[2].first);
        setupPointsPlayerLabel(&pointsWonPlayerLabel4, sortedPlayerScores[3].second, sortedPlayerScores[3].first);
    }
}

void GameInfoWidget::updateTeamPoints(map<int, int> teamScores, pair<Team, Team> teams)
{
    auto setupPointsTeamLabel = [this](ScaledQLabel *label, int score, Team team) {
        if (team.empty()) // teams not known yet
        {
            label->setText("???");
        }
        else
        {
            string text = getTeamName(team) + ": " + to_string(score);
            label->setText(QString::fromStdString(text));
        }
    };

    if (teamScores.empty() || teams.first.empty() || teams.second.empty())
    {
        setupPointsTeamLabel(&pointsWonTeamLabel1, 0, Team());
        setupPointsTeamLabel(&pointsWonTeamLabel2, 0, Team());
    }
    else
    {
        auto getTeam = [&teams](int teamNum) {
            switch (teamNum)
            {
            case TEAM_1:
                return teams.first;
            case TEAM_2:
                return teams.second;
            default:
                return Team();
            }
        };

        vector<pair<int, int>> sortedTeamScores;

        for (auto It = teamScores.begin(); It != teamScores.end(); It++)
        {
            sortedTeamScores.push_back(make_pair(It->first, It->second));
        }

        sort(sortedTeamScores.begin(), sortedTeamScores.end(), ScoreCompare());

        setupPointsTeamLabel(&pointsWonTeamLabel1, sortedTeamScores[0].second, getTeam(sortedTeamScores[0].first));
        setupPointsTeamLabel(&pointsWonTeamLabel2, sortedTeamScores[1].second, getTeam(sortedTeamScores[1].first));
    }
}

string GameInfoWidget::getTeamName(Team team)
{
    if (team.empty())
        return "";

    string teamName = "???";

    for (auto playerNum : team)
    {
        if (teamName == "???")
            teamName = gc.playerArr[playerNum].getPlayerName();
        else
            teamName = teamName + " + " + gc.playerArr[playerNum].getPlayerName();
    }

    return teamName;
}