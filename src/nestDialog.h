#ifndef NESTDIALOG_H
#define NESTDIALOG_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <string>

#include "card.h"
#include "clickableCard.h"
#include "common.h"

using namespace std;

// forward declarations
class GameController;

// global declarations
extern GameController gc;

// for selecting cards from nest
class NestDialog : public QDialogWithClickableCardArray
{
    CardVector originalNest;
    CardStyleMap originalNestStyles;

private:
    QMainWindow *mainWindow; 

    ScaledQPushButton autoChooseNestButton;
    ScaledQPushButton resetNestButton;
    ScaledQPushButton doneNestButton;

    ScaledQLabel centerCardsLabel;
    ClickableCardArray centerCards;

    ScaledQLabel bottomCardsPreviewLabel;
    ClickableCardArray bottomCardsPreview;

    ScaledQCheckBox highlightCardsCheckBox;

public:
    NestDialog(CardVector pOriginalNest, QMainWindow *pMainWindow, QWidget *parent = nullptr);
    virtual void rescale();
    
    void setOriginalNestStyles(string style);

    virtual void onCardClicked(ClickableCard *clickableCard);
    virtual void onCardHoverEnter(ClickableCard *clickableCard);
    virtual void onCardHoverLeave(ClickableCard *clickableCard);

    static void autoChooseNest();

    void autoChooseNestButtonPressed();
    void resetNestButtonPressed();
    void doneNestButtonPressed();
    void highlightCardsCheckBoxPressed();
};

#endif