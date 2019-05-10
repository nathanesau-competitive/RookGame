#include "mainWindow.h"
#include "bidDialog.h"
#include "trumpDialog.h"

#include <QApplication>
#include <string>
#include <algorithm>
#include <vector>

#include <QSize>
#include <QRect>
#include <QDesktopWidget>

using namespace std;

void moveDialogToCenter(QDialog *dialog)
{
    auto mwPos = gui.mw->pos();
    auto mwSize = gui.mw->size();
    auto mwCenter = QPoint(mwPos.x() + mwSize.width() / 2,
                           mwPos.y() + mwSize.height() / 2);

    auto dialogSize = dialog->size();

    auto dialogTopLeft = QPoint(mwCenter.x() - dialogSize.width() / 2,
                                mwCenter.y() - dialogSize.height() / 2);

    dialog->move(dialogTopLeft);
}

void showMessageBox(QString msg, QString title)
{
    MessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setWindowTitle(title);
    moveDialogToCenter(&msgBox);
    msgBox.exec();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    widget.setParent(this);

    bottomCards.setParent(&widget);

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

    hideWidgets();
}

void MainWindow::hideWidgets()
{
    bottomCards.hideCards();
}

void MainWindow::drawBottomCards(vector<Card> &cardArr)
{
    bottomCards.showCards(cardArr, DRAW_POSITION_BOTTOM);
}

void MainWindow::onCardClicked(ClickableCard *clickableCard)
{
    Card card = clickableCard->data;

    if (gc.currentPhase == PHASE_MIDDLE)
    {
        auto &nest = gc.nest;
        auto &hand = gc.playerArr[PLAYER_1].cardArr;

        auto nestIt = std::find(nest.begin(), nest.end(), card);
        auto handIt = std::find(hand.begin(), hand.end(), card);

        if (nestIt != nest.end())
        {
            nest.erase(nestIt);

            hand.push_back(card);
            sortCardArray(hand);
            bottomCards.showCards(hand, DRAW_POSITION_BOTTOM);
        }
        else // handIt != hand.end()
        {
            hand.erase(handIt);
            bottomCards.showCards(hand, DRAW_POSITION_BOTTOM);

            nest.push_back(card);
            sortCardArray(nest);
        }
    }
    else if (gc.currentPhase == PHASE_PLAY)
    {
        // todo
    }
}

void MainWindow::onTrumpClicked(TrumpLabel *trumpLabel)
{
    gc.trump = SUIT_BLACK;
}

void MainWindow::onNewGameAction()
{
    gc.newGame();

    bottomCards.showCards(gc.playerArr[PLAYER_1].cardArr, DRAW_POSITION_BOTTOM);

    BidDialog bidDlg;
    moveDialogToCenter(&bidDlg);
    auto bidDlgFinished = bidDlg.exec();

    if (!bidDlgFinished)
    {
        return; // todo: show some error here, close application
    }

    // todo: only show nest if PLAYER_1 won bid
    NestDialog nestDlg;
    moveDialogToCenter(&nestDlg);
    auto nestDlgFinished = nestDlg.exec();

    if (!nestDlgFinished)
    {
        return; // todo: show some error here, close application
    }

    TrumpDialog trumpDlg;
    moveDialogToCenter(&trumpDlg);
    auto trumpDlgFinished = trumpDlg.exec();

    if (!trumpDlgFinished)
    {
        return; // todo: show some error here, close application
    }

    /*centerCards.showCards(gc.nest, DRAW_POSITION_CENTER);
    autoChooseMiddleButton.show();
    doneMiddleButton.show();
    */
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