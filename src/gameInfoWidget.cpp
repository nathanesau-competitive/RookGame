#include <QToolTip>

#include "card.h"
#include "gameController.h"
#include "gameInfoWidget.h"
#include "player.h"
#include "utils.h"

GameInfoWidget::GameInfoWidget(QMainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                            QDialogWithClickableCardArray(parent)
{
    auto setupCategoryLabel = [this](QLabel *categoryLabel, QString text, QPoint pos) {
        categoryLabel->setParent(this);
        categoryLabel->setText(text);
        categoryLabel->setFont(QFont("Times", 12, QFont::Weight::Bold));
        categoryLabel->move(pos);
    };

    auto setupLabel = [this](QLabel *label, QString text, QSize size, QPoint pos) {
        label->setParent(this);
        label->setText(text);
        label->setFont(QFont("Times", 10, QFont::Weight::Normal));
        label->resize(size);
        label->move(pos);
    };

    setupCategoryLabel(&bidCategoryLabel, "Bid", {25, 10});
    setupLabel(&bidPlayerLabel, "???", {100, 20}, {35, 35});
    setupLabel(&bidAmountLabel, "???", {100, 20}, {35, 55});

    setupCategoryLabel(&partnerCardCategoryLabel, "Partner", {135, 10});
    topLeftCards.setParent(this);

    setupCategoryLabel(&trumpCategoryLabel, "Trump", {270, 10});
    setupLabel(&trumpLabel, "???", {50, 20}, {280, 35});
    trumpLabel.setAlignment(Qt::AlignHCenter);

    setupCategoryLabel(&pointsMiddleCategoryLabel, "Points Middle", {380, 10});
    setupLabel(&pointsMiddleLabel, "???", {125, 20}, {390, 35});

    setupCategoryLabel(&teamsCategoryLabel, "Teams", {530, 10});
    setupLabel(&team1Label, "???", {150, 20}, {540, 35});
    setupLabel(&team2Label, "???", {150, 20}, {540, 55});

    setupCategoryLabel(&pointsWonTeamCategoryLabel, "Points (by Team)", {690, 10});
    setupLabel(&pointsWonTeamLabel1, "???", {150, 20}, {700, 35});
    setupLabel(&pointsWonTeamLabel2, "???", {150, 20}, {700, 55});

    setupCategoryLabel(&pointsWonPlayerCategoryLabel, "Points (by Player)", {890, 10});
    setupLabel(&pointsWonPlayerLabel1, "Player 1: 0", {100, 20}, {900, 35});
    setupLabel(&pointsWonPlayerLabel2, "Player 2: 0", {100, 20}, {900, 55});
    setupLabel(&pointsWonPlayerLabel3, "Player 3: 0", {100, 20}, {900, 75});
    setupLabel(&pointsWonPlayerLabel4, "Player 4: 0", {100, 20}, {900, 95});

    setupCategoryLabel(&overallScoresCategoryLabel, "Scores", {1080, 10});
    setupLabel(&player1OverallScoreLabel, "Player 1: 0", {100, 20}, {1090, 35});
    setupLabel(&player2OverallScoreLabel, "Player 2: 0", {100, 20}, {1090, 55});
    setupLabel(&player3OverallScoreLabel, "Player 3: 0", {100, 20}, {1090, 75});
    setupLabel(&player4OverallScoreLabel, "Player 4: 0", {100, 20}, {1090, 95});

    setStyleSheet("background-color: white");
}

void GameInfoWidget::resetInfoToDefaults()
{
    updateBid(PLAYER_UNDEFINED, 0, true);
    updatePoints(map<int, int>(), map<int, int>(), make_pair(set<int>(), set<int>()));
    updateOverallScores(0, 0, 0, 0);
    updatePartner(Card());
    updateTrump(SUIT_UNDEFINED);
    updatePointsMiddle(0, true);
    updateTeam1({});
    updateTeam2({});
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
    }(gc.partnerPair.second);

    QToolTip::showText(mainWindow->pos() + clickableCard->pos(), toolTipText, clickableCard);
}

void GameInfoWidget::onCardHoverLeave(ClickableCard *clickableCard)
{
    // do nothing
}

void GameInfoWidget::updateBid(int playerNum, int amount, bool showBlankAmount)
{
    bidPlayerLabel.setText(QString::fromStdString(Utils::Ui::getPlayerName(playerNum)));

    if (showBlankAmount)
    {
        bidAmountLabel.setText("???");
    }
    else
    {
        bidAmountLabel.setText(QString::number(amount));
    }
}

void GameInfoWidget::updatePartner(Card partnerCard, int playerNum)
{
    topLeftCards.showCards({partnerCard}, DRAW_POSITION_GAME_INFO_WIDGET, SIZE_TINY);
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

void GameInfoWidget::updateTeam1(set<int> team1)
{
    team1Label.setText(QString::fromStdString(Utils::Ui::getTeamName(team1)));
}

void GameInfoWidget::updateTeam2(set<int> team2)
{
    team2Label.setText(QString::fromStdString(Utils::Ui::getTeamName(team2)));
}

void GameInfoWidget::updatePoints(map<int, int> playerScores, map<int, int> teamScores, pair<set<int>, set<int>> teams)
{
    auto setupPointsPlayerLabel = [this](QLabel *label, int score, int playerNum) {
        string text = Utils::Ui::getPlayerName(playerNum) + ": " + to_string(score);
        label->setText(QString::fromStdString(text));
    };

    auto setupPointsTeamLabel = [this](QLabel *label, int score, set<int> team) {
        if (team.empty()) // teams not known yet
        {
            label->setText("???");
        }
        else
        {
            string text = Utils::Ui::getTeamName(team) + ": " + to_string(score);
            label->setText(QString::fromStdString(text));
        }
    };

    auto getTeam = [&teams](int teamNum) {
        switch (teamNum)
        {
        case TEAM_1:
            return teams.first;
        case TEAM_2:
            return teams.second;
        default:
            return set<int>();
        }
    };

    struct ScoreCompare
    {
        inline bool operator()(const pair<int, int> &score1, const pair<int, int> &score2)
        {
            if (score1.second < score2.second)
            {
                return false;
            }
            else if(score1.second == score2.second)
            {
                return score1.first < score2.first;
            }
            else 
            {
                return true;
            }
        }
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

    if (teamScores.empty() || teams.first.empty() || teams.second.empty())
    {
        setupPointsTeamLabel(&pointsWonTeamLabel1, 0, set<int>());
        setupPointsTeamLabel(&pointsWonTeamLabel2, 0, set<int>());
    }
    else
    {
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

void GameInfoWidget::updateOverallScores(int player1Score, int player2Score, int player3Score, int player4Score)
{
    auto setupLabel = [this](QLabel *label, int score, int playerNum) {
        string text = Utils::Ui::getPlayerName(playerNum) + ": " + to_string(score);
        label->setText(QString::fromStdString(text));
    };

    setupLabel(&player1OverallScoreLabel, player1Score, PLAYER_1);
    setupLabel(&player2OverallScoreLabel, player2Score, PLAYER_2);
    setupLabel(&player3OverallScoreLabel, player3Score, PLAYER_3);
    setupLabel(&player4OverallScoreLabel, player4Score, PLAYER_4);
}