#ifndef NESTDIALOG_H
#define NESTDIALOG_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "clickableCard.h"
#include "common.h"

// forward declarations
class GameController;

// global declarations
extern GameController gc;

// for selecting cards from nest
class NestDialog : public QDialogWithClickableCardArray
{
    QMainWindow *mainWindow;

    ScaledQPushButton autoChooseNestButton;
    ScaledQPushButton doneNestButton;

    ScaledQLabel centerCardsLabel;
    ClickableCardArray centerCards;

    ScaledQLabel bottomCardsPreviewLabel;
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

#endif