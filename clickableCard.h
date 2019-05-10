#ifndef CLICKABLECARD_H
#define CLICKABLECARD_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QDialog>

#include "gameController.h"

// constants
// todo - cleanup DRAW constant names and get position code (dynamic position cases)

const int DRAW_POSITION_BOTTOM = 0;           // main widget
const int DRAW_POSITION_CENTER = 1;           // nest dialog
const int DRAW_POSITION_CENTER_PREVIEW = 2;   // nest dialog
const int DRAW_POSITION_PARTNER_DLG_ROW1 = 3; // trump partner sub dialog
const int DRAW_POSITION_PARTNER_DLG_ROW2 = 4; // trump partner sub dialog
const int DRAW_POSITION_PARTNER_DLG_ROW3 = 5; // trump partner sub dialog
const int DRAW_POSITION_TRUMP_DLG = 6;        // trump dialog
const int DRAW_POSITION_TOP_LEFT = 7;         // game info widget

const int DRAW_POSITION_CARD_PLAYED_BOTTOM = 8; // main widget
const int DRAW_POSITION_CARD_PLAYED_LEFT = 9; // main widget
const int DRAW_POSITION_CARD_PLAYED_TOP = 10; // main widget
const int DRAW_POSITION_CARD_PLAYED_RIGHT = 11; // main widget

const int SIZE_NORMAL = 0;
const int SIZE_SMALL = 1;
const int SIZE_TINY = 2;

// forward declarations
struct Interface;

// global declarations
extern Interface gui;

class ClickableCard : public QLabel
{
    Q_OBJECT

public:
    Card data;

    // IMPORTANT: parent be derived class of QDialogWithClickableCardArray
    ClickableCard(QWidget *parent = nullptr);
    ClickableCard(const ClickableCard &pCard);
    ClickableCard &operator=(const ClickableCard &pCard);

    // Only difference from QLabel class is setData method
    // and override mousePressEvent
    void setData(const Card &pData, const int drawPosition, int size = SIZE_NORMAL);

protected:
    void mousePressEvent(QMouseEvent *event);
};

class ClickableCardArray : public QObject
{
    vector<ClickableCard> clickableCards;

public:
    ClickableCardArray(QWidget *parent = nullptr);

    void showCards(const vector<Card> &cardArr, const int drawPosition, const int size = SIZE_NORMAL);
    void hideCards();

private:
    QPoint getCardPosition(int n, int index, const int drawPosition);
};

class QDialogWithClickableCardArray : public QDialog
{
public:
    QDialogWithClickableCardArray(QWidget *parent = nullptr);

    virtual void onCardClicked(ClickableCard *clickableCard) = 0;
};

#endif