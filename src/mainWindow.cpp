#include <algorithm>
#include <QRect>
#include <QSize>
#include <QThread>
#include <string>
#include <vector>

#include "bidDialog.h"
#include "card.h"
#include "clickableCard.h"
#include "gameInfoWidget.h"
#include "gameController.h"
#include "mainWindow.h"
#include "messageBox.h"
#include "middleDialog.h"
#include "preferencesDialog.h"
#include "PreferencesDialog.h"
#include "utils.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) : ScaledQMainWindow(parent),
                                          widget(this)
{
    widget.setParent(this);
    widget.infoWidget.updatePartner(Card(SUIT_UNDEFINED, VALUE_UNDEFINED));

    newGameAction.setText(QMenu::tr("&New"));
    newGameAction.setShortcuts(QKeySequence::New);
    newGameAction.setStatusTip("Start a new game");
    QObject::connect(&newGameAction, &QAction::triggered, this, &MainWindow::onNewGameAction);

    loadGameAction.setText(QMenu::tr("&Load"));
    loadGameAction.setShortcuts(QKeySequence::Open);
    loadGameAction.setStatusTip("Load an existing game");
    QObject::connect(&loadGameAction, &QAction::triggered, this, &MainWindow::onLoadGameAction);

    saveGameAction.setText(QMenu::tr("&Save"));
    saveGameAction.setShortcuts(QKeySequence::Save);
    saveGameAction.setStatusTip("Save the current game");
    QObject::connect(&saveGameAction, &QAction::triggered, this, &MainWindow::onSaveGameAction);

    preferencesAction.setText(QMenu::tr("&Preferences"));
    preferencesAction.setShortcuts(QKeySequence::Preferences);
    preferencesAction.setStatusTip("Edit the preferences");
    QObject::connect(&preferencesAction, &QAction::triggered, this, &MainWindow::onPreferencesAction);

    exitAction.setText(QMenu::tr("&Exit"));
    exitAction.setShortcuts(QKeySequence::Quit);
    exitAction.setStatusTip("Exit the game");
    QObject::connect(&exitAction, &QAction::triggered, this, &MainWindow::onExitAction);

    fileMenu.setTitle(QMenu::tr("&File"));
    fileMenu.addAction(&newGameAction);
    fileMenu.addAction(&loadGameAction);
    fileMenu.addAction(&saveGameAction);
    fileMenu.addAction(&preferencesAction);
    fileMenu.addAction(&exitAction);

    viewScoresAction.setText(QMenu::tr("View scores"));
    viewScoresAction.setStatusTip("View scores for current game");
    QObject::connect(&viewScoresAction, &QAction::triggered, this, &MainWindow::onViewScoresAction);

    gameMenu.setTitle(QMenu::tr("&Game"));
    gameMenu.addAction(&viewScoresAction);

    checkUpdatesAction.setText(QMenu::tr("Check for Updates"));
    checkUpdatesAction.setStatusTip("Check for game updates");
    QObject::connect(&checkUpdatesAction, &QAction::triggered, this, &MainWindow::onCheckUpdatesAction);

    aboutAction.setText(QMenu::tr("About"));
    aboutAction.setStatusTip("Info about the game");
    QObject::connect(&aboutAction, &QAction::triggered, this, &MainWindow::onAboutAction);

    helpMenu.setTitle(QMenu::tr("&Help"));
    helpMenu.addAction(&checkUpdatesAction);
    helpMenu.addAction(&aboutAction);

    menuBar.addMenu(&fileMenu);
    menuBar.addMenu(&gameMenu);
    menuBar.addMenu(&helpMenu);

    setCentralWidget(&widget);
    setWindowTitle("Rook");
    setWindowIcon(QIcon(":rookicon.gif"));
    setMenuBar(&menuBar);
    setGeometry(QRect(0, 0, 1200, 850));

    QPixmap bkgnd(":background.PNG");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);
}

void MainWindow::rescale()
{
    ScaledQMainWindow::rescale();
    widget.rescale();

    Utils::Ui::moveWindowToCenter(this, 36);
}

void MainWindow::onNewGameAction()
{
    widget.infoWidget.resetOverallInfoToDefaults();

    MessageBox msgBox;
    Utils::Ui::setupMessageBox(&msgBox, "Previous scores cleared. Starting new game...", "New game");
    Utils::Ui::moveDialog(&msgBox, this, DIALOG_POSITION_CENTER);
    msgBox.exec();

    startNewRound();
}

void MainWindow::onLoadGameAction()
{
    // todo
}

void MainWindow::onSaveGameAction()
{
    // save overall scores to sql
    // todo
}

void MainWindow::onPreferencesAction()
{
    PreferencesDialog preferencesDlg(this);
    auto result = preferencesDlg.exec();

    Utils::Db::writePreferences();
}

void MainWindow::onExitAction()
{
    // todo
}

void MainWindow::onViewScoresAction()
{
    // todo
}

void MainWindow::onCheckUpdatesAction()
{
    // todo
}

void MainWindow::onAboutAction()
{
    MessageBox msgBox(this);
    msgBox.setText("Hello world");
    msgBox.exec();
}

void MainWindow::startNewRound()
{
    // clear existing info
    widget.infoWidget.resetRoundInfoToDefaults();
    widget.player1CardPlayed.hideCards();
    widget.player2CardPlayed.hideCards();
    widget.player3CardPlayed.hideCards();
    widget.player4CardPlayed.hideCards();
    widget.bottomCards.hideCards();
    widget.centerCards.hideCards();

    showNewRoundMessage();

    gc.onNewGame();

    widget.bottomCards.showCards(gc.playerArr[PLAYER_1].cardArr);

    BidDialog bidDlg(this);
    Utils::Ui::moveDialog(&bidDlg, this, DIALOG_POSITION_CENTER);
    auto player1WonBid = bidDlg.exec();

    widget.infoWidget.updateBid(gc.roundInfo.bidPlayer, gc.roundInfo.bidAmount);

    if (player1WonBid)
    {
        int trumpSuitSelected = SUIT_UNDEFINED;
        Card partnerCardSelected = Card(SUIT_UNDEFINED, VALUE_UNDEFINED);

        MiddleDialog middleDlg(trumpSuitSelected, partnerCardSelected, &widget, this);
        Utils::Ui::moveDialog(&middleDlg, this, DIALOG_POSITION_MIDDLE_DLG);

        if (!middleDlg.exec())
        {
            qFatal("Problem executing middle dialog");
            return;
        }

        gc.roundInfo.trump = trumpSuitSelected;
        gc.roundInfo.partnerCard = partnerCardSelected;
    }

    // set rook suit to trump suit
    auto modifyRookSuit = []() {
        for (auto playerNum : vector<int>{PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4})
        {
            for (auto &card : gc.playerArr[playerNum].cardArr)
            {
                if (card.suit == SUIT_SPECIAL)
                {
                    card.suit = gc.roundInfo.trump;

                    return playerNum;
                }
            }
        }

        return PLAYER_UNDEFINED;
    };

    if (modifyRookSuit() == PLAYER_1) // player 1 has the rook card
    {
        // re-sort and redraw bottom cards
        gc.playerArr[PLAYER_1].cardArr.sort(gc.roundInfo.trump);
        widget.bottomCards.showCards(gc.playerArr[PLAYER_1].cardArr);
    }

    gc.roundInfo.pointsMiddle = gc.nest.getNumPoints();

    widget.infoWidget.updateTrump(gc.roundInfo.trump);
    widget.infoWidget.updatePartner(gc.roundInfo.partnerCard);
    widget.infoWidget.updatePointsMiddle(gc.roundInfo.pointsMiddle);

    MessageBox msgBox;
    Utils::Ui::setupMessageBox(&msgBox, "Trump, partner, points in middle updated.\n\nGame starting.", "Start Game");
    Utils::Ui::moveDialog(&msgBox, this, DIALOG_POSITION_CENTER);
    msgBox.exec();

    // play first few cards if necessary
    widget.startNewHand(gc.roundInfo.bidPlayer);
}

void MainWindow::showNewRoundMessage()
{
    MessageBox msgBox;
    Utils::Ui::setupMessageBox(&msgBox, "A new round is starting...", "New round");
    Utils::Ui::moveDialog(&msgBox, this, DIALOG_POSITION_CENTER);
    msgBox.exec();
}
