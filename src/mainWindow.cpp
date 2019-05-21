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
#include "utils.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
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
    setGeometry(0, 0, 1200, 850);
    setMaximumSize(QSize(1200, 850));
    setFixedSize(maximumSize());

    QPixmap bkgnd(":background.PNG");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);
}

void MainWindow::onTrumpClicked(TrumpLabel *trumpLabel)
{
    gc.trump = SUIT_BLACK;
}

void MainWindow::onNewGameAction()
{
    gc.newGame();

    widget.infoWidget.resetInfoToDefaults();
    widget.showBottomCards(gc.playerArr[PLAYER_1].cardArr);

    BidDialog bidDlg(this);
    Utils::Ui::moveDialogToCenter(&bidDlg, this);

    if (!bidDlg.exec())
    {
        qFatal("Problem executing big dialog");
        return;
    }

    widget.infoWidget.updateBid(gc.bidPlayer, gc.bidAmount);

    int trumpSuitSelected = SUIT_UNDEFINED;
    Card partnerCardSelected = Card(SUIT_UNDEFINED, VALUE_UNDEFINED);

    // todo: only show middle dialog if PLAYER_1 won bid
    MiddleDialog middleDlg(trumpSuitSelected, partnerCardSelected, &widget, this);
    Utils::Ui::moveDialogToCenter(&middleDlg, this, {0, -50});

    if (!middleDlg.exec())
    {
        qFatal("Problem executing middle dialog");
        return;
    }

    int pointsMiddle = []() {
        int total = 0;
        for (auto &card : gc.nest)
        {
            total += card.getPointValue();
        }
        return total;
    }();

    widget.infoWidget.updateTrump(trumpSuitSelected);
    widget.infoWidget.updatePartner(partnerCardSelected);
    widget.infoWidget.updatePointsMiddle(pointsMiddle);

    gc.pointsMiddle = pointsMiddle;
    gc.trump = trumpSuitSelected;
    gc.partnerPair.first = partnerCardSelected;

    MessageBox msgBox;
    Utils::Ui::setupMessageBox(&msgBox, "Trump, partner, points in middle updated.\n\nGame starting.", "Start Game");
    Utils::Ui::moveDialogToCenter(&msgBox, this);
    msgBox.exec();
}

void MainWindow::onLoadGameAction()
{
    // todo
}

void MainWindow::onSaveGameAction()
{
    // todo
}

void MainWindow::onPreferencesAction()
{
    // todo
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
    // todo
}