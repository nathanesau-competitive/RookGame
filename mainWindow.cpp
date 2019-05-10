#include "mainWindow.h"
#include "bidDialog.h"
#include "trumpDialog.h"

#include <QApplication>
#include <string>
#include <QThread>
#include <algorithm>
#include <vector>

#include <QSize>
#include <QRect>
#include <QDesktopWidget>

using namespace std;

namespace Utils
{
namespace Ui
{
void moveDialogToCenter(QDialog *dialog, int VERTICAL_SHIFT, int HORIZONTAL_SHIFT)
{
    auto mwPos = gui.mw->pos();
    auto mwSize = gui.mw->size();
    auto mwCenter = QPoint(mwPos.x() + mwSize.width() / 2,
                           mwPos.y() + mwSize.height() / 2);

    auto dialogSize = dialog->size();

    auto dialogTopLeft = QPoint(mwCenter.x() - dialogSize.width() / 2 + HORIZONTAL_SHIFT,
                                mwCenter.y() - dialogSize.height() / 2 + VERTICAL_SHIFT);

    dialog->move(dialogTopLeft);
}

void showMessageBox(QString msg, QString title, int VERTICAL_SHIFT, int HORIZONTAL_SHIFT, QSize size)
{
    MessageBox msgBox;
    msgBox.resize(size);
    msgBox.setText(msg);
    msgBox.setWindowTitle(title);
    Utils::Ui::moveDialogToCenter(&msgBox, VERTICAL_SHIFT, HORIZONTAL_SHIFT);
    msgBox.exec();
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
        return "Unknown player"; // not implemented
    }
}
} // namespace Ui
} // namespace Utils

GameInfoWidget::GameInfoWidget(QWidget *parent) : QDialogWithClickableCardArray(parent)
{
    auto setupCategoryLabel = [this](QLabel *categoryLabel, QString text, QPoint pos) {
        categoryLabel->setParent(this);
        categoryLabel->setText(text);
        categoryLabel->setFont(QFont("Times", 12, QFont::Weight::Bold));
        categoryLabel->move(pos);
    };

    auto setupLabel = [this](QLabel *label, QString text, QSize size, QPoint pos) {
        label->setParent(this);
        label->setText(text);
        label->setFont(QFont("Times", 10, QFont::Weight::Normal));
        label->resize(size);
        label->move(pos);
    };

    setupCategoryLabel(&partnerCardCategoryLabel, "Partner", {25, 10});
    topLeftCards.setParent(this);

    setupCategoryLabel(&trumpCategoryLabel, "Trump", {180, 10});
    setupLabel(&trumpLabel, "None selected", {105, 50}, {205, 35});

    setupCategoryLabel(&pointsMiddleCategoryLabel, "Points Middle", {340, 10});
    setupLabel(&pointsMiddleLabel, "No middle cards selected", {150, 50}, {365, 35});

    setupCategoryLabel(&roundScoresCategoryLabel, "Round Scores", {575, 10});
    setupLabel(&player1RoundScoreLabel, "Player 1: 0", {100, 50}, {600, 35});
    setupLabel(&player2RoundScoreLabel, "Player 2: 0", {100, 50}, {600, 85});
    setupLabel(&player3RoundScoreLabel, "Player 3: 0", {100, 50}, {720, 35});
    setupLabel(&player4RoundScoreLabel, "Player 4: 0", {100, 50}, {720, 85});

    setupCategoryLabel(&overallScoresCategoryLabel, "Overall Scores", {865, 10});
    setupLabel(&player1OverallScoreLabel, "Player 1: 0", {100, 50}, {890, 35});
    setupLabel(&player2OverallScoreLabel, "Player 2: 0", {100, 50}, {890, 85});
    setupLabel(&player3OverallScoreLabel, "Player 3: 0", {100, 50}, {1010, 35});
    setupLabel(&player4OverallScoreLabel, "Player 4: 0", {100, 50}, {1010, 85});

    setStyleSheet("background-color: white");
}

void GameInfoWidget::resetInfoToDefaults()
{
    updateRoundScores(0,0,0,0);
    updateOverallScores(0,0,0,0);
    updatePartner(Card());
    updateTrump(SUIT_UNDEFINED);
    updatePointsMiddle(0);
}

void GameInfoWidget::onCardClicked(ClickableCard *clickableCard)
{
    // do nothing
}

void GameInfoWidget::updatePartner(Card partnerCard)
{
    topLeftCards.showCards({partnerCard}, DRAW_POSITION_TOP_LEFT, SIZE_TINY);
}

void GameInfoWidget::updateTrump(int trumpSuit)
{
    switch (trumpSuit)
    {
    case SUIT_BLACK:
        trumpLabel.setStyleSheet("background-color: black; color: white");
        trumpLabel.setText("Black");
        break;
    case SUIT_GREEN:
        trumpLabel.setStyleSheet("background-color: green");
        trumpLabel.setText("Green");
        break;
    case SUIT_RED:
        trumpLabel.setStyleSheet("background-color: red");
        trumpLabel.setText("Red");
        break;
    case SUIT_YELLOW:
        trumpLabel.setStyleSheet("background-color: yellow");
        trumpLabel.setText("Yellow");
        break;
    default:
        trumpLabel.setStyleSheet("");
        trumpLabel.setText("None selected");
        break;
    }
}

void GameInfoWidget::updatePointsMiddle(int pointsMiddle)
{
    pointsMiddleLabel.setText(QString::number(pointsMiddle));
}

void GameInfoWidget::updateRoundScores(int player1Score, int player2Score, int player3Score, int player4Score)
{
    auto setupLabel = [this](QLabel *label, int score, int playerNum) {
        string text = Utils::Ui::getPlayerName(playerNum) + ": " + to_string(score);
        label->setText(QString::fromStdString(text));
    };

    setupLabel(&player1RoundScoreLabel, player1Score, PLAYER_1);
    setupLabel(&player2RoundScoreLabel, player2Score, PLAYER_2);
    setupLabel(&player3RoundScoreLabel, player3Score, PLAYER_3);
    setupLabel(&player4RoundScoreLabel, player4Score, PLAYER_4);
}

void GameInfoWidget::updateOverallScores(int player1Score, int player2Score, int player3Score, int player4Score)
{
    auto setupLabel = [this](QLabel *label, int score, int playerNum) {
        string text = Utils::Ui::getPlayerName(playerNum) + ": " + to_string(score);
        label->setText(QString::fromStdString(text));
    };

    setupLabel(&player1OverallScoreLabel, player1Score, PLAYER_1);
    setupLabel(&player2OverallScoreLabel, player2Score, PLAYER_2);
    setupLabel(&player3OverallScoreLabel, player3Score, PLAYER_3);
    setupLabel(&player4OverallScoreLabel, player4Score, PLAYER_4);
}

MainWidget::MainWidget(QWidget *parent) : QDialogWithClickableCardArray(parent)
{
    infoWidget.setParent(this);
    infoWidget.move(QPoint(0, 0));
    infoWidget.resize(1200, 130);

    player1CardPlayed.setParent(this);
    player2CardPlayed.setParent(this);
    player3CardPlayed.setParent(this);
    player4CardPlayed.setParent(this);

    bottomCards.setParent(this);
}

void MainWidget::onCardClicked(ClickableCard *clickableCard)
{
    // todo: MAKE sure it is a card in player 1's hand otherwise don't do anything (i.e. ignore click on played cards)

    Card card = clickableCard->data;

    gc.playHand(card);

    showBottomCards(gc.playerArr[PLAYER_1].cardArr);

    showCardPlayed(card, PLAYER_1);
    repaint();

    QThread::msleep(500);

    showCardPlayed(gc.handInfo.cardPlayed[PLAYER_2], PLAYER_2);
    repaint();

    QThread::msleep(500);

    showCardPlayed(gc.handInfo.cardPlayed[PLAYER_3], PLAYER_3);
    repaint();

    QThread::msleep(500);

    showCardPlayed(gc.handInfo.cardPlayed[PLAYER_4], PLAYER_4);
    repaint();

    //QThread::msleep(500);

    infoWidget.updateRoundScores(gc.scores[PLAYER_1], gc.scores[PLAYER_2],
                            gc.scores[PLAYER_3], gc.scores[PLAYER_4]);

    Utils::Ui::showMessageBox("Player 1 won the hand", "Hand result", 0, 400, {200, 220});

    player1CardPlayed.hideCards();
    player2CardPlayed.hideCards();
    player3CardPlayed.hideCards();
    player4CardPlayed.hideCards();
}

void MainWidget::showCardPlayed(const Card &card, int playerNum)
{
    // todo: implement timer
    switch (playerNum)
    {
    case PLAYER_1:
        player1CardPlayed.showCards({card}, DRAW_POSITION_CARD_PLAYED_BOTTOM);
        break;
    case PLAYER_2:
        player2CardPlayed.showCards({card}, DRAW_POSITION_CARD_PLAYED_LEFT);
        break;
    case PLAYER_3:
        player3CardPlayed.showCards({card}, DRAW_POSITION_CARD_PLAYED_TOP);
        break;
    case PLAYER_4:
        player4CardPlayed.showCards({card}, DRAW_POSITION_CARD_PLAYED_RIGHT);
        break;
    }
}

void MainWidget::showBottomCards(const vector<Card> &cardArr)
{
    bottomCards.showCards(cardArr, DRAW_POSITION_BOTTOM);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
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

    BidDialog bidDlg;
    Utils::Ui::moveDialogToCenter(&bidDlg);
    auto bidDlgFinished = bidDlg.exec();

    if (!bidDlgFinished)
    {
        return; // todo: show some error here, close application
    }

    // todo: only show nest if PLAYER_1 won bid
    NestDialog nestDlg;
    Utils::Ui::moveDialogToCenter(&nestDlg, -40);
    auto nestDlgFinished = nestDlg.exec();

    if (!nestDlgFinished)
    {
        return; // todo: show some error here, close application
    }

    widget.showBottomCards(gc.playerArr[PLAYER_1].cardArr);

    int trumpSuitSelected = SUIT_UNDEFINED;
    Card partnerCardSelected = Card(SUIT_UNDEFINED, VALUE_UNDEFINED);

    TrumpDialog trumpDlg(trumpSuitSelected, partnerCardSelected);
    Utils::Ui::moveDialogToCenter(&trumpDlg);
    auto trumpDlgFinished = trumpDlg.exec();

    if (!trumpDlgFinished)
    {
        return; // todo: show some error here, close application
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

    Utils::Ui::showMessageBox("Game starting...", "Start Game");

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