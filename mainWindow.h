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
void moveDialogToCenter(QDialog *dialog);
void showMessageBox(QString msg, QString title);

class MainWindow : public QMainWindow
{
    QWidget widget; // central widget

    ClickableCardArray bottomCards;

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

    void hideWidgets();

    void drawBottomCards(vector<Card> &cardArr);

    void onCardClicked(ClickableCard *clickableCard);
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