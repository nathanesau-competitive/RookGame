#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QLabel>
#include <QMenuBar>
#include <QString>
#include <QObject>
#include <QMenu>
#include <QListView>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPoint>
#include <QSize>
#include <QPushButton>
#include <QMessageBox>
#include <string>

#include "bidDialog.h"
#include "nestDialog.h"
#include "clickableCard.h"
#include "gameController.h"
#include "trumpDialog.h"
#include "messageBox.h"

using namespace std;

// global declarations
extern GameController gc;

namespace Utils
{
namespace Ui
{
void moveDialogToCenter(QDialog *dialog, int VERTICAL_SHIFT = 0, int HORIZONTAL_SHIFT = 0);
void showMessageBox(QString msg, QString title, int VERTICAL_SHIFT = 0, int HORIZONTAL_SHIFT = 0, QSize size = {477, 220});
string getPlayerName(int playerNum);
} // namespace Ui
} // namespace Utils

class GameInfoWidget : public QDialogWithClickableCardArray
{
public:
    QLabel partnerCardCategoryLabel; // i.e. PARTNER
    ClickableCardArray topLeftCards; // i.e. [14 black]

    QLabel trumpCategoryLabel; // i.e. TRUMP
    QLabel trumpLabel;         // i.e. [Red]

    QLabel pointsMiddleCategoryLabel; // i.e. POINTS IN MIDDLE
    QLabel pointsMiddleLabel;         // i.e. Yes

    QLabel roundScoresCategoryLabel; // i.e. ROUND SCORES
    QLabel player1RoundScoreLabel; // i.e. [20]
    QLabel player2RoundScoreLabel; // i.e. [50]
    QLabel player3RoundScoreLabel; // i.e. [0]
    QLabel player4RoundScoreLabel; // i.e. [0]

    QLabel overallScoresCategoryLabel; // i.e. OVERALL SCORES
    QLabel player1OverallScoreLabel;
    QLabel player2OverallScoreLabel;
    QLabel player3OverallScoreLabel;
    QLabel player4OverallScoreLabel;

    GameInfoWidget(QWidget *parent = nullptr);

    void resetInfoToDefaults();

    virtual void onCardClicked(ClickableCard *clickableCard);

    void updatePartner(Card partnerCard);
    void updateTrump(int trumpSuit);
    void updatePointsMiddle(int pointsMiddle);
    void updateRoundScores(int player1Score, int player2Score, int player3Score, int player4Score);
    void updateOverallScores(int player1Score, int player2Score, int player3Score, int player4Score);
};

class MainWidget : public QDialogWithClickableCardArray
{
public:
    GameInfoWidget infoWidget;

    ClickableCardArray player1CardPlayed;
    ClickableCardArray player2CardPlayed;
    ClickableCardArray player3CardPlayed;
    ClickableCardArray player4CardPlayed;

    ClickableCardArray bottomCards;

    MainWidget(QWidget *parent = nullptr);

    virtual void onCardClicked(ClickableCard *clickableCard);

    void showCardPlayed(const Card &card, int playerNum);
    void showBottomCards(const vector<Card> &cardArr);
};

class MainWindow : public QMainWindow
{
    MainWidget widget; // central widget

    QMenu fileMenu;
    QAction newGameAction;
    QAction loadGameAction;
    QAction saveGameAction;
    QAction preferencesAction;
    QAction exitAction;

    QMenu gameMenu;
    QAction viewScoresAction;

    QMenu helpMenu;
    QAction checkUpdatesAction;
    QAction aboutAction;

    QMenuBar menuBar;

public:
    MainWindow(QWidget *parent = nullptr);

    //void onCardClicked(ClickableCard *clickableCard);
    void onTrumpClicked(TrumpLabel *trumpLabel);

    void onNewGameAction();
    void onLoadGameAction();
    void onSaveGameAction();
    void onPreferencesAction();
    void onExitAction();
    void onViewScoresAction();
    void onCheckUpdatesAction();
    void onAboutAction();
};

// widget globals
struct Interface
{
    MainWindow *mw;
};

#endif