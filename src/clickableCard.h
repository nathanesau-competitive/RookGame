#ifndef CLICKABLECARD_H
#define CLICKABLECARD_H

#include <QDialog>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QWidget>
#include <vector>

#include "card.h"
#include "common.h"

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
const int DRAW_POSITION_PARTNER_DLG = 9;
const int DRAW_POSITION_GAME_INFO_WIDGET = 10;
const int DRAW_POSITION_MESSAGE_BOX = 111;

const QSize SIZE_UNDEFINED = {0, 0};
const QSize SIZE_NORMAL = {180, 180};
const QSize SIZE_SMALL = {135, 135};
const QSize SIZE_TINY = {90, 90};

// forward declarations
class QDialogWithClickableCardArray;

class ClickableCard : public ScaledQLabel
{
    Q_OBJECT

public:
    Card data;

    ClickableCard(QDialogWithClickableCardArray *parent = nullptr);
    ClickableCard(const ClickableCard &pCard);
    ClickableCard &operator=(const ClickableCard &pCard);

    // Only difference from QLabel class is setData method
    // and override mousePressEvent
    void setData(const Card &pData, int drawPosition, QSize size = SIZE_NORMAL);

protected:
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

class ClickableCardArray
{
    QDialogWithClickableCardArray *parent;

    vector<ClickableCard> clickableCards;

    int drawPosition;
    QSize size;

public:
    ClickableCardArray(int pDrawPosition, QSize pSize = SIZE_NORMAL, QDialogWithClickableCardArray *pParent = nullptr);

    void showCards(const vector<Card> &cardArr);
    void hideCards();

private:
    QPoint getCardPosition(int i, int n);
};

class QDialogWithClickableCardArray : public ScaledQDialog
{
public:
    QDialogWithClickableCardArray(QWidget *parent = nullptr);

    virtual void onCardClicked(ClickableCard *clickableCard) = 0;
    virtual void onCardHoverEnter(ClickableCard *clickableCard) = 0;
    virtual void onCardHoverLeave(ClickableCard *clickableCard) = 0;
};

#endif