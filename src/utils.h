#ifndef UTILS_H
#define UTILS_H

#include <QComboBox>
#include <QDialog>
#include <QFont>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <set>
#include <string>

#include "card.h"
#include "messageBox.h"

using namespace std;

// constants
const int DIALOG_POSITION_CENTER = 0;
const int DIALOG_POSITION_MIDDLE_DLG = 1;
const int DIALOG_POSITION_NEST_DLG = 2;
const int DIALOG_POSITION_TRUMP_DLG = 3;
const int DIALOG_POSITION_PARTNER_DLG = 4;
const int DIALOG_POSITION_CARD_MESSAGE_BOX = 5;

// forward declarations
class GameController;
class MainWindow;

// global declarations
extern GameController gc;

namespace Utils
{
namespace Ui
{
float getScaleFactor(float desiredScreenRatio);
void moveWindowToCenter(QMainWindow *mainWindow, int taskBarHeight);

// use QDialog not ScaledQDialog to ensure dialog is always centered
// todo: moveDialogToCenter
// todo: moveDialogToCenterRight
// todo: moveDialogToCenterLeft
// todo: moveDialogToCenterTop
// ...
void moveDialog(QDialog *dialog, QMainWindow *mainWindow, int position);

void setupMessageBox(MessageBox *msgBox, QString msg, QString title, QSize = {477, 250});

string getPlayerName(int playerNum);

string getTeamName(set<int> team);

// for custom widgets, scale functions declared inside header files
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