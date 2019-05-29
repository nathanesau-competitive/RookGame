#ifndef UTILS_H
#define UTILS_H

#include <QComboBox>
#include <QDialog>
#include <QFont>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSize>
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
class HandInfo;
class MainWindow;
class RoundInfo;

namespace Utils
{
namespace Ui
{
float getBestScaleFactor();
QSize getResolution(float scaleFactor);
void moveWindowToCenter(QMainWindow *mainWindow, int taskBarHeight);
void moveDialog(QDialog *dialog, QMainWindow *mainWindow, int position);
void setupMessageBox(MessageBox *msgBox, QString msg, QString title, QSize = {477, 250});
} // namespace Ui

namespace Db
{
void readPreferences();
void writePreferences();
} // namespace Db

namespace Stat
{
double phi(double x); // standard normal distribution cdf
}

} // namespace Utils

#endif