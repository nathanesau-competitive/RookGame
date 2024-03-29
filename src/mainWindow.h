#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <string>

#include "common.h"
#include "mainWidget.h"

#include <memory>

using namespace std;

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class MainWindow : public ScaledQMainWindow
{
    MainWidget *widget; // central widget

    QMenu *fileMenu;
    QAction* newGameAction;
    QAction* loadGameAction;
    QAction* quitAction;

    QMenu *editMenu;
    QAction *preferencesAction;

    QMenu *gameMenu;
    QAction* viewScoresAction;

    QMenu *helpMenu;
    QAction *checkUpdatesAction;
    QAction *aboutAction;

public:
    MainWindow(QWidget *parent = nullptr);

    void rescale();

    // preferences dialog - appearance page
    void updatePlayerNames(map<int, string> playerNames);
    void updateNameTags(bool showNameTags);

    void onNewGameAction();
    void onLoadGameAction();
    void onSaveGameAction();
    void onPreferencesAction();
    void onQuitAction();
    void onViewScoresAction();
    void onCheckUpdatesAction();
    void onAboutAction();

    void startNewRound();
    void showNewRoundMessage();
};

#endif