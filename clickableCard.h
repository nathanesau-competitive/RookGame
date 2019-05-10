#ifndef CLICKABLECARD_H
#define CLICKABLECARD_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QDialog>

#include "gameController.h"

// constants
const int DRAW_POSITION_BOTTOM = 0;
const int DRAW_POSITION_CENTER = 1;
const int DRAW_POSITION_PARTNER_DLG_ROW1 = 2;
const int DRAW_POSITION_PARTNER_DLG_ROW2 = 3;
const int DRAW_POSITION_PARTNER_DLG_ROW3 = 4;
const int DRAW_POSITION_TRUMP_DLG = 5;

const int DRAW_POSITION_TOP_LEFT = 6; // main widget

const int SIZE_NORMAL = 0;
const int SIZE_SMALL = 1; // for partner card dialog

// forward declarations
struct Interface;

// global declarations
extern Interface gui;

class ClickableCard : public QLabel
{
    Q_OBJECT // mousePressEvent

        public : Card data;

    ClickableCard(QWidget *parent = nullptr);
    ClickableCard(const ClickableCard &pCard);
    ClickableCard &operator=(const ClickableCard &pCard);

    // Only difference from QLabel class is setData method
    // and override mousePressEvent
    void setData(const Card &pData, int size = SIZE_NORMAL);

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