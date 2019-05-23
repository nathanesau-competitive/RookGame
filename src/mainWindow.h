#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <string>

#include "common.h"
#include "mainWidget.h"

using namespace std;

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class MainWindow : public ScaledQMainWindow
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

    void onNewGameAction();
    void onLoadGameAction();
    void onSaveGameAction();
    void onPreferencesAction();
    void onExitAction();
    void onViewScoresAction();
    void onCheckUpdatesAction();
    void onAboutAction();
};

#endif