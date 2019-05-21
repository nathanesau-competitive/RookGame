#ifndef UTILS_H
#define UTILS_H

#include <QDialog>
#include <QMainWindow>
#include <set>
#include <string>

#include "card.h"
#include "messageBox.h"

using namespace std;

// forward declarations
class GameController;

// global declarations
extern GameController gc;

namespace Utils
{
namespace Ui
{
void moveDialogToCenter(QDialog *dialog, QMainWindow *mainWindow, const QPoint &offset = {0,0});

void setupMessageBox(MessageBox *msgBox, QString msg, QString title, QSize = {477, 250});

string getPlayerName(int playerNum);

string getTeamName(set<int> team);
}

namespace Game
{
void sortCardArray(vector<Card> &cardArr, int trump = SUIT_UNDEFINED);

vector<SuitInfo> getSuitInfoArray(vector<Card> &cardArr);

vector<Card> getAggregateCardArray(vector<const vector<Card> *> &cardArrays);

bool cardArrHasSuit(vector<Card> &cardArr, int suit);

vector<Card> getPlayableCards(vector<Card> &cardArr);

Card getBestCard(vector<Card> &playableCardArr);

void incrementPlayerNum(int &playerNum);
}

namespace Stat
{
double phi(double x); // standard normal distribution cdf
}

} // namespace Utils

#endif