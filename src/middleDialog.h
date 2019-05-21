#ifndef MIDDLEDIALOG_H
#define MIDDLEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "card.h"
#include "clickableCard.h"
#include "trumpLabel.h"
#include "ui_MiddleDialog.h"

namespace Ui
{
class MiddleDialog;
}

// forward declarations
class GameController;
class MainWidget;

// global declarations
extern GameController gc;

class MiddleDialog : public QDialogWithClickableCardArray
{
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

// for selecting cards from nest
class NestDialog : public QDialogWithClickableCardArray
{
    QMainWindow *mainWindow;

    QPushButton autoChooseNestButton;
    QPushButton doneNestButton;

    QLabel centerCardsLabel;
    ClickableCardArray centerCards;

    QLabel bottomCardsPreviewLabel;
    ClickableCardArray bottomCardsPreview;

public:
    NestDialog(QMainWindow *pMainWindow, QWidget *parent = nullptr);
    virtual ~NestDialog();
    
    virtual void onCardClicked(ClickableCard *clickableCard);

    virtual void onCardHoverEnter(ClickableCard *clickableCard)
    {
        // do nothing
    }

    virtual void onCardHoverLeave(ClickableCard *clickableCard)
    {
        // do nothing
    }

    static void autoChooseNest();

    void autoChooseNestButtonPressed();
    void doneNestButtonPressed();
};

// for selecting a trump suit
class TrumpDialog : public QDialog
{
    int &suitSelected;

    TrumpLabel blackLabel;
    TrumpLabel greenLabel;
    TrumpLabel redLabel;
    TrumpLabel yellowLabel;

public:
    TrumpDialog(int &pSuitSelected, QWidget *parent = nullptr);
    virtual ~TrumpDialog();

    void onTrumpLabelClicked(TrumpLabel *label);
};

// for selecting a partner card from available cards
class PartnerDialog : public QDialogWithClickableCardArray
{
    Card &cardSelected;

    ClickableCardArray blackCards;
    ClickableCardArray greenCards;
    ClickableCardArray redCards;
    ClickableCardArray yellowCards;
    ClickableCardArray specialCards;

public:
    PartnerDialog(Card &pCardSelected, QWidget *parent = nullptr);
    virtual ~PartnerDialog();

    virtual void onCardClicked(ClickableCard *clickableCard);

    virtual void onCardHoverEnter(ClickableCard *clickableCard)
    {
        // do nothing
    }

    virtual void onCardHoverLeave(ClickableCard *clickableCard)
    {
        // do nothing
    }
};

#endif