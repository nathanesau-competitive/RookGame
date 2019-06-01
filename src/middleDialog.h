#ifndef MIDDLEDIALOG_H
#define MIDDLEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "card.h"
#include "clickableCard.h"
#include "common.h"
#include "ui_MiddleDialog.h"

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class MiddleDialog : public QDialogWithClickableCardArray
{
    CardVector originalNest;

    int &trumpSuitSelected;
    Card &partnerCardSelected;

private:
    MainWidget *mainWidget;
    QMainWindow *mainWindow;

    ClickableCardArray topRightCards;
    ClickableCardArray bottomRightCards;

public:
    MiddleDialog(int &pTrumpSuitSelected, Card &pPartnerCardSelected, MainWidget *pMainWidget, QMainWindow *pMainWindow, QWidget *parent = nullptr);
    virtual void rescale();

    virtual void onCardClicked(ClickableCard *clickableCard);
    virtual void onCardHoverEnter(ClickableCard *clickableCard);
    virtual void onCardHoverLeave(ClickableCard *clickableCard);

private:
    Ui::MiddleDialog ui;

    void selectNestButtonPressed();
    void autoSelectNestButtonPressed();
    void selectTrumpButtonPressed();
    void autoSelectTrumpButtonPressed();
    void selectPartnerButtonPressed();
    void autoSelectPartnerButtonPressed();
    void okButtonPressed();

    void setupTrumpLabel(int suit);
};

#endif