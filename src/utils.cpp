#include <QApplication>
#include <QDesktopWidget>

#include "bidDialog.h"
#include "ui_BidDialog.h"
#include "clickableCard.h"
#include "gameController.h"
#include "mainWidget.h"
#include "mainWindow.h"
#include "messageBox.h"
#include "ui_MessageBox.h"
#include "middleDialog.h"
#include "ui_MiddleDialog.h"
#include "roundSummaryDialog.h"
#include "utils.h"

namespace Utils
{
namespace Ui
{
float getScaleFactor(float desiredScreenRatio)
{
    float screenRatio = min(0.925F, desiredScreenRatio);

    QSize origSize = {1200, 850};
    QRect maxSize = QApplication::desktop()->screenGeometry(); // i.e. 1920x1080
    float factor = min((float)maxSize.width() / origSize.width(),
                       (float)maxSize.height() / origSize.height());

    return factor * screenRatio;
}

void moveWindowToCenter(QMainWindow *mainWindow, int taskBarHeight)
{
    auto screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - mainWindow->width()) / 2;
    int y = max(0, (screenGeometry.height() - mainWindow->height()) / 2 - taskBarHeight);
    mainWindow->move(QPoint(x, y));
}

void moveDialog(QDialog *dialog, QMainWindow *mainWindow, int position)
{
    auto mainWindowPos = mainWindow->pos();
    auto mainWindowSize = mainWindow->size();
    auto mainWindowCenter = QPoint(mainWindowPos.x() + mainWindowSize.width() / 2,
                                   mainWindowPos.y() + mainWindowSize.height() / 2);

    auto dialogSize = dialog->size();

    auto dialogPos = [&]() -> QPoint {
        auto centerPos = QPoint(mainWindowCenter.x() - dialogSize.width() / 2,
                                mainWindowCenter.y() - dialogSize.height() / 2);

        switch (position)
        {
        case DIALOG_POSITION_CENTER:
            return centerPos;

        case DIALOG_POSITION_MIDDLE_DLG:
            return QPoint(centerPos.x(), centerPos.y() - mainWindowSize.height() * 0.1F);

        case DIALOG_POSITION_NEST_DLG:
            return QPoint(centerPos.x(), centerPos.y() - mainWindowSize.height() * 0.1F);

        case DIALOG_POSITION_TRUMP_DLG:
            return QPoint(centerPos.x(), centerPos.y() - mainWindowSize.height() * 0.1F);

        case DIALOG_POSITION_PARTNER_DLG:
            return QPoint(centerPos.x(), centerPos.y() - mainWindowSize.height() * 0.1F);

        case DIALOG_POSITION_CARD_MESSAGE_BOX:
            return QPoint(centerPos.x() + mainWindowSize.width() * 0.35F, centerPos.y());

        default:
            return {0, 0};
        }
    }();

    dialog->move(QPoint({max(0, dialogPos.x()), max(0, dialogPos.y())}));
}

void setupMessageBox(MessageBox *msgBox, QString msg, QString title, QSize size)
{
    msgBox->setText(msg);
    msgBox->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    msgBox->resize(size);
    msgBox->setWindowTitle(title);
}

string getPlayerName(int playerNum) // player name to display on screen
{
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
        return "???"; // not implemented
    }
}

string getTeamName(set<int> team)
{
    string teamName = "???";

    for (auto playerNum : team)
    {
        auto playerName = Utils::Ui::getPlayerName(playerNum);
        teamName = (teamName == "???") ? playerName : teamName + " + " + playerName;
    }

    return teamName;
}

} // namespace Ui

namespace Game
{
void sortCardArray(vector<Card> &cardArr, int trump)
{
    struct CardCompare
    {
        int pTrump;

        CardCompare(int trump) : pTrump(trump)
        {
        }

        inline bool operator()(const Card &card1, const Card &card2)
        {
            if (pTrump != SUIT_UNDEFINED && card1.suit == pTrump && card2.suit != pTrump)
            {
                return false;
            }
            else if (card1.suit < card2.suit)
            {
                return true;
            }
            else if (card1.suit == card2.suit)
            {
                if (card1.value < card2.value)
                {
                    return true;
                }
            }

            return false;
        }
    };

    sort(cardArr.begin(), cardArr.end(), CardCompare(trump));
}

// used for auto-selecting middle cards
vector<SuitInfo> getSuitInfoArray(vector<Card> &cardArr)
{
    struct SuitInfoCompareCount // ascending order
    {
        inline bool operator()(const SuitInfo &info1, const SuitInfo &info2)
        {
            return info1.count > info2.count;
        }
    };

    struct SuitInfoCompareTotalValue // ascending order
    {
        inline bool operator()(const SuitInfo &info1, const SuitInfo &info2)
        {
            return info1.totalValue > info2.totalValue;
        }
    };

    vector<int> suitArr = {SUIT_BLACK, SUIT_GREEN, SUIT_RED, SUIT_YELLOW, SUIT_SPECIAL};
    vector<SuitInfo> suitInfoArr;

    for (auto suit : suitArr)
    {
        suitInfoArr.push_back(SuitInfo(suit));
    }

    for (auto &card : gc.playerArr[PLAYER_1].cardArr)
    {
        auto It = std::find(suitInfoArr.begin(), suitInfoArr.end(), SuitInfo(card.suit));

        if (card.suit == SUIT_SPECIAL)
        {
            It->count += 1;
            It->totalValue = 100; // ALWAYS keep this card (TRUMP)
        }
        else
        {
            It->count += 1;
            It->totalValue += card.value;
        }
    }

    sort(suitInfoArr.begin(), suitInfoArr.end(), SuitInfoCompareCount());
    sort(suitInfoArr.begin(), suitInfoArr.end(), SuitInfoCompareTotalValue());

    return suitInfoArr;
}

vector<Card> getAggregateCardArray(vector<const vector<Card> *> &cardArrays)
{
    auto fillCardArray = [](vector<Card> &outCardArr, const vector<Card> &inCardArr) {
        for (auto card : inCardArr)
        {
            outCardArr.push_back(card);
        }
    };

    vector<Card> aggregateCardArr;

    for (auto cardArr : cardArrays)
    {
        if (cardArr)
        {
            fillCardArray(aggregateCardArr, *cardArr);
        }
    }

    return aggregateCardArr;
}

bool cardArrHasSuit(vector<Card> &cardArr, int suit)
{
    for (auto card : cardArr)
    {
        if (card.suit == suit)
        {
            return true;
        }
    }

    return false;
}

vector<Card> getPlayableCards(vector<Card> &cardArr)
{
    int suit = gc.handInfo.suit;

    if (cardArrHasSuit(cardArr, suit))
    {
        vector<Card> playableCards;

        for (auto card : cardArr)
        {
            if (card.suit == suit)
            {
                playableCards.push_back(card);
            }
        }

        return playableCards;
    }
    else
    {
        return cardArr; // all cards are playable
    }
}

Card getBestCard(vector<Card> &playableCardArr)
{
    int suit = gc.handInfo.suit;

    Utils::Game::sortCardArray(playableCardArr, suit);

    return playableCardArr[playableCardArr.size() - 1];
}

void incrementPlayerNum(int &playerNum)
{
    switch (playerNum)
    {
    case PLAYER_1:
        playerNum = PLAYER_2;
        return;
    case PLAYER_2:
        playerNum = PLAYER_3;
        return;
    case PLAYER_3:
        playerNum = PLAYER_4;
        return;
    case PLAYER_4:
        playerNum = PLAYER_1;
        return;
    default:
        playerNum = PLAYER_UNDEFINED;
        return;
    }
}
} // namespace Game

namespace Stat
{
double phi(double x)
{
    // constants
    double a1 = 0.254829592;
    double a2 = -0.284496736;
    double a3 = 1.421413741;
    double a4 = -1.453152027;
    double a5 = 1.061405429;
    double p = 0.3275911;

    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x) / sqrt(2.0);

    // A&S formula 7.1.26
    double t = 1.0 / (1.0 + p * x);
    double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

    return 0.5 * (1.0 + sign * y);
}
} // namespace Stat

} // namespace Utils