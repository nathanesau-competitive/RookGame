#ifndef MIDDLEDIALOG_H
#define MIDDLEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "card.h"
#include "clickableCard.h"
#include "common.h"
#include "ui_MiddleDialog.h" // uic -o ui_middleDialog.h middleDialog.ui

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class MiddleDialog : public QDialogWithClickableCardArray
{
    CardVector originalNest;

    int &trumpSuitSelected; // output of dialog
    Card &partnerCardSelected; // output of dialog

private:
    MainWidget *mainWidget; // non-owning
    QMainWindow *mainWindow; // non-owning

    ClickableCardArray *topRightCards;
    ClickableCardArray *bottomRightCards;

public:
    MiddleDialog(int &pTrumpSuitSelected, Card &pPartnerCardSelected, MainWidget *pMainWidget, QMainWindow *pMainWindow, QWidget *parent = nullptr);
    virtual void rescale();

    void reject() {}

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