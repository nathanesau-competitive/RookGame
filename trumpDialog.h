#ifndef TRUMPDIALOG_H
#define TRUMPDIALOG_H

#include <QDialog>
#include <QLabel>

#include "trumpLabel.h"
#include "mainWindow.h"

namespace Ui
{
class TrumpDialog;
}

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class TrumpDialog : public QDialogWithClickableCardArray
{
    int &trumpSuitSelected;
    Card &partnerCardSelected;

    ClickableCardArray bottomRightCards;

public:
    TrumpDialog(int &pTrumpSuitSelected, Card &pPartnerCardSelected, QWidget *parent = nullptr);
    virtual ~TrumpDialog();

    virtual void onCardClicked(ClickableCard *clickableCard);

private:
    Ui::TrumpDialog *ui;

    void selectSuitButtonPressed();
    void autoSelectSuitButtonPressed();
    void selectCardButtonPressed();
    void autoSelectCardButtonPressed();
    void okButtonPressed();

    void setupTrumpLabel(int suit);
};

// for selecting a trump suit
class TrumpSuitSubDialog : public QDialog
{
    int &suitSelected;

    TrumpLabel blackLabel;
    TrumpLabel greenLabel;
    TrumpLabel redLabel;
    TrumpLabel yellowLabel;

public:
    TrumpSuitSubDialog(int &pSuitSelected, QWidget *parent = nullptr);
    virtual ~TrumpSuitSubDialog();

    void onTrumpLabelClicked(TrumpLabel *label);
};

// for selecting a partner card from available cards
class TrumpPartnerSubDialog : public QDialogWithClickableCardArray
{
    Card &cardSelected;

    ClickableCardArray blackCards;
    ClickableCardArray greenCards;
    ClickableCardArray redCards;
    ClickableCardArray yellowCards;
    ClickableCardArray specialCards;

public:
    TrumpPartnerSubDialog(Card &pCardSelected, QWidget *parent = nullptr);
    virtual ~TrumpPartnerSubDialog();

    virtual void onCardClicked(ClickableCard *clickableCard);
};

#endif