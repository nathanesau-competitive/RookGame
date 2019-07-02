#include <QString>
#include <QPoint>
#include <QSize>

#include "gameMenuWidget.h"
#include "mainWindow.h"

GameMenuWidget::GameMenuWidget(MainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                           ScaledQDialog(parent)
{
    auto setupButton = [this](ScaledQPushButton *button, QString text, QPoint pos, QSize size) {
        button->setParent(this);
        button->setText(text);
        button->setFont(QFont("Times", 10));
        button->move(pos);
        button->resize(size.width(), size.height());
    };

    menuTitleLabel.setParent(this);
    menuTitleLabel.setText("Game Menu");
    menuTitleLabel.setFont(QFont("Times", 12));
    menuTitleLabel.move({25, 25});
    menuTitleLabel.resize(100, 25);

    setupButton(&newGameButton, "New Game", {125, 75}, {100, 25});
    setupButton(&newRoundButton, "New Round", {125, 120}, {100, 25});
    setupButton(&saveGameButton, "Save Game", {125, 165}, {100, 25});
    setupButton(&loadGameButton, "Load Game", {125, 210}, {100, 25});
    setupButton(&quitGameButton, "Quit Game", {125, 255}, {100, 25});

    QObject::connect(&newGameButton, &QPushButton::pressed, this, &GameMenuWidget::onNewGameButtonPressed);
    QObject::connect(&newRoundButton, &QPushButton::pressed, this, &GameMenuWidget::onNewRoundButtonPressed);
    QObject::connect(&saveGameButton, &QPushButton::pressed, this, &GameMenuWidget::onSaveGameButtonPressed);
    QObject::connect(&loadGameButton, &QPushButton::pressed, this, &GameMenuWidget::onLoadGameButtonPressed);
    QObject::connect(&quitGameButton, &QPushButton::pressed, this, &GameMenuWidget::onQuitGameButtonPressed);

    setStyleSheet("background-color: white");
}

void GameMenuWidget::rescale()
{
    updateScaleFactor();
    setGeometry(geometry());

    for (auto label : vector<ScaledQLabel *>{&menuTitleLabel})
        label->rescale();

    for (auto button : vector<ScaledQPushButton *>{&newGameButton, &newRoundButton, &saveGameButton,
                                                   &loadGameButton, &quitGameButton})
        button->rescale();
}

void GameMenuWidget::onNewGameButtonPressed()
{
    mainWindow->onNewGameAction();
}

void GameMenuWidget::onNewRoundButtonPressed()
{
    mainWindow->startNewRound();
}

void GameMenuWidget::onSaveGameButtonPressed()
{
    mainWindow->onSaveGameAction();
}

void GameMenuWidget::onLoadGameButtonPressed()
{
    mainWindow->onLoadGameAction();
}

void GameMenuWidget::onQuitGameButtonPressed()
{
    mainWindow->close();
}