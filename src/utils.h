#ifndef UTILS_H
#define UTILS_H

#include <QComboBox>
#include <QDialog>
#include <QFont>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSize>
#include <QString>
#include <set>
#include <string>

#include "card.h"
#include "messageBox.h"
#include "player.h"

using namespace std;

// constants
const int DIALOG_POSITION_CENTER = 0;
const int DIALOG_POSITION_MIDDLE_DLG = 1;
const int DIALOG_POSITION_NEST_DLG = 2;
const int DIALOG_POSITION_TRUMP_DLG = 3;
const int DIALOG_POSITION_PARTNER_DLG = 4;
const int DIALOG_POSITION_CARD_MESSAGE_BOX = 5;

// forward declarations
class HandInfo;
class MainWindow;
class RoundInfo;

namespace Utils
{
namespace Ui
{
QRect getScreenGeometry();
float getBestScaleFactor();
QSize getResolution(float scaleFactor);
void moveWindowToCenter(QWidget *widget, int taskBarHeight = 0);
void moveDialog(QDialog *dialog, QMainWindow *mainWindow, int position);
void setupMessageBox(MessageBox *msgBox, QString msg, QString title, QSize = {477, 250});
} // namespace Ui

namespace Db
{
float readScaleFactorFromDb();
map<int, string> readPlayerNamesFromDb();
bool readShowNameTagsFromDb();
bool readShowPartnerToolTipFromDb();
int readScreenWidthFromDb();
int readScreenHeightFromDb();

void writeScaleFactorToDb(float scaleFactor);
void writePlayerNamesToDb(map<int, string> playerNames);
void writeShowNameTagsToDb(bool showNameTags);
void writeShowPartnerToolTipToDb(bool showPartnerToolTip);
void writeScreenWidthToDb(int screenWidth);
void writeScreenHeightToDb(int screenHeight);
} // namespace Db

namespace Stat
{
double phi(double x); // standard normal distribution cdf
}

} // namespace Utils

#endif