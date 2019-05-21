#ifndef CLICKABLECARD_H
#define CLICKABLECARD_H

#include <QDialog>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QWidget>
#include <vector>

#include "card.h"

using namespace std;

const int DRAW_POSITION_UNDEFINED = -1;
const int DRAW_POSITION_MAIN_WIDGET_BOTTOM = 0;
const int DRAW_POSITION_MAIN_WIDGET_CENTER_BOTTOM = 1;
const int DRAW_POSITION_MAIN_WIDGET_CENTER_LEFT = 2;
const int DRAW_POSITION_MAIN_WIDGET_CENTER_TOP = 3;
const int DRAW_POSITION_MAIN_WIDGET_CENTER_RIGHT = 4;
const int DRAW_POSITION_MIDDLE_DLG_NEST = 5;
const int DRAW_POSITION_MIDDLE_DLG_PARTNER = 6;
const int DRAW_POSITION_NEST_DLG_TOP = 7;
const int DRAW_POSITION_NEST_DLG_BOTTOM = 8;
const int DRAW_POSITION_PARTNER_DLG_ROW1 = 9;
const int DRAW_POSITION_PARTNER_DLG_ROW2 = 10;
const int DRAW_POSITION_PARTNER_DLG_ROW3 = 11;
const int DRAW_POSITION_GAME_INFO_WIDGET = 12;
const int DRAW_POSITION_MESSAGE_BOX = 13;

const int SIZE_UNDEFINED = -1;
const int SIZE_NORMAL = 0;
const int SIZE_SMALL = 1;
const int SIZE_TINY = 2;

// forward declarations
class QDialogWithClickableCardArray;

class ClickableCard : public QLabel
{
    Q_OBJECT

public:
    Card data;

    ClickableCard(QDialogWithClickableCardArray *parent = nullptr);
    ClickableCard(const ClickableCard &pCard);
    ClickableCard &operator=(const ClickableCard &pCard);

    // Only difference from QLabel class is setData method
    // and override mousePressEvent
    void setData(const Card &pData, const int drawPosition, int size = SIZE_NORMAL);

protected:
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

class ClickableCardArray : public QObject
{
    vector<ClickableCard> clickableCards;

    int drawPosition;
    int size;

public:
    ClickableCardArray(QWidget *parent = nullptr);

    void showCards(const vector<Card> &cardArr, const int pDrawPosition, const int pSize = SIZE_NORMAL);
    void hideCards();

private:
    QPoint getCardPosition(int i, int n, const int drawPosition, const int size);
};

class QDialogWithClickableCardArray : public QDialog
{
public:
    QDialogWithClickableCardArray(QWidget *parent = nullptr);

    virtual void onCardClicked(ClickableCard *clickableCard) = 0;
    virtual void onCardHoverEnter(ClickableCard *clickableCard) = 0;
    virtual void onCardHoverLeave(ClickableCard *clickableCard) = 0;
};

#endif