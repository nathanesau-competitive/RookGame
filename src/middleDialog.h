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

    MainWidget *mainWidget;
    QMainWindow *mainWindow;

    int &trumpSuitSelected;
    Card &partnerCardSelected;

    ClickableCardArray topRightCards;
    ClickableCardArray bottomRightCards;

public:
    MiddleDialog(int &pTrumpSuitSelected, Card &pPartnerCardSelected, MainWidget *pMainWidget, QMainWindow *pMainWindow, QWidget *parent = nullptr);
    virtual ~MiddleDialog();

    virtual void onCardClicked(ClickableCard *clickableCard);
    
    virtual void onCardHoverEnter(ClickableCard *clickableCard)
    {
        // do nothing
    }

    virtual void onCardHoverLeave(ClickableCard *clickableCard)
    {
        // do nothing
    }

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