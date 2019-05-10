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

#include "bidDialog.h"
#include "nestDialog.h"
#include "clickableCard.h"
#include "gameController.h"
#include "trumpDialog.h"
#include "messageBox.h"

using namespace std;

// global declarations
extern GameController gc;

// global functions
void moveDialogToCenter(QDialog *dialog, int VERTICAL_SHIFT = 0);
void showMessageBox(QString msg, QString title);

class GameInfoWidget : public QDialogWithClickableCardArray
{
public:
    QLabel partnerCardCategoryLabel; // i.e. PARTNER
    ClickableCardArray topLeftCards; // i.e. [14 black]

    QLabel trumpCategoryLabel; // i.e. TRUMP
    QLabel trumpLabel;         // i.e. [Red]

    QLabel pointsMiddleCategoryLabel; // i.e. POINTS IN MIDDLE
    QLabel pointsMiddleLabel;         // i.e. Yes

    QLabel scoresCategoryLabel;       // i.e. SCORES
    QLabel player1ScoreLabel;
    QLabel player2ScoreLabel;
    QLabel player3ScoreLabel;
    QLabel player4ScoreLabel;

    GameInfoWidget(QWidget *parent = nullptr);

    virtual void onCardClicked(ClickableCard *clickableCard);

    void updatePartner(Card partnerCard);
    void updateTrump(int trumpSuit);
    void updatePointsMiddle(int pointsMiddle);
    void updateScores(int player1Score, int player2Score, int player3Score, int player4Score);
};

class MainWidget : public QDialogWithClickableCardArray
{
public:
    GameInfoWidget infoWidget;
    ClickableCardArray bottomCards;

    MainWidget(QWidget *parent = nullptr);

    virtual void onCardClicked(ClickableCard *clickableCard);
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

    void drawBottomCards(const vector<Card> &cardArr);

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