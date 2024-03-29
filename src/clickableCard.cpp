#include <QBrush>
#include <QPainter>

#include "clickableCard.h"
#include "mainWindow.h"

ClickableCard::ClickableCard(QDialogWithClickableCardArray *parent) : ScaledQLabel(parent)
{
}

ClickableCard::ClickableCard(const ClickableCard &pCard) : data(pCard.data)
{
    // not set: parent, pixmap, stylesheet
}

ClickableCard &ClickableCard::operator=(const ClickableCard &pCard)
{
    // not set: parent, pixmap, stylesheet

    this->data = pCard.data;
    return *this;
}

void ClickableCard::setData(const Card &pData, int drawPosition, QSize size, string style)
{
    if (data != pData || data == Card(SUIT_UNDEFINED, VALUE_UNDEFINED))
    {
        data = pData;

        auto pixmapKey = CardPixmapKey(data,
                                       size.width() * scalefactor,
                                       size.height() * scalefactor,
                                       getRotation(drawPosition));

        auto &pixmap = pixmapcache[pixmapKey];

        if (!pixmap)
        {
            string fname = ":" + pixmapKey.data.getValueAsString() + pixmapKey.data.getSuitAsString() + ".gif";
            QTransform transform;
            transform.rotate(pixmapKey.rotation);
            pixmap.reset(new QPixmap(QString::fromStdString(fname)));
            *pixmap = pixmap->scaled(QSize(pixmapKey.width, pixmapKey.height),
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
            *pixmap = pixmap->transformed(transform);
            QLabel::setPixmap(*pixmap);
        }
        else
        {
            QLabel::setPixmap(*pixmap);
        }

        setStyleSheet(QString::fromStdString(style));
    }
}

void ClickableCard::mousePressEvent(QMouseEvent *event)
{
    auto parentWidgetWithClickableCardArray = dynamic_cast<QDialogWithClickableCardArray *>(parent());

    parentWidgetWithClickableCardArray->onCardClicked(this);
}

void ClickableCard::enterEvent(QEvent *event)
{
    auto parentWidgetWithClickableCardArray = dynamic_cast<QDialogWithClickableCardArray *>(parent());

    parentWidgetWithClickableCardArray->onCardHoverEnter(this);
}

void ClickableCard::leaveEvent(QEvent *event)
{
    auto parentWidgetWithClickableCardArray = dynamic_cast<QDialogWithClickableCardArray *>(parent());

    parentWidgetWithClickableCardArray->onCardHoverLeave(this);
}

int ClickableCard::getRotation(int drawPosition)
{
    switch (drawPosition)
    {
    case DRAW_POSITION_MAIN_WIDGET_CENTER_LEFT:
        return 90;
    case DRAW_POSITION_MAIN_WIDGET_CENTER_TOP:
        return 180;
    case DRAW_POSITION_MAIN_WIDGET_CENTER_RIGHT:
        return 270;
    default:
        return 0;
    }
}

CardKey::CardKey(Card pData) : data(pData)
{
}

bool CompareCardKey::operator()(const CardKey &a, const CardKey &b) const
{
    if (a.data.suit < b.data.suit)
    {
        return true;
    }
    else if (a.data.suit == b.data.suit)
    {
        if (a.data.value < b.data.value)
        {
            return true;
        }
    }

    return false;
}

CardPixmapKey::CardPixmapKey(Card pData, int pWidth, int pHeight, int pRotation) : data(pData),
                                                                                   width(pWidth),
                                                                                   height(pHeight),
                                                                                   rotation(pRotation)
{
}

bool CompareCardPixmapKey::operator()(const CardPixmapKey &a, const CardPixmapKey &b) const
{
    if (a.data.suit < b.data.suit)
    {
        return true;
    }
    else if (a.data.suit == b.data.suit)
    {
        if (a.data.value < b.data.value)
        {
            return true;
        }
        else if (a.data.value == b.data.value)
        {
            if (a.width < b.width)
            {
                return true;
            }
            else if (a.width == b.width)
            {
                if (a.height < b.height)
                {
                    return true;
                }
                else if (a.height == b.height)
                {
                    if (a.rotation < b.rotation)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

ClickableCardArray::ClickableCardArray(int pDrawPosition, QSize pSize, QDialogWithClickableCardArray *parent) : QWidget(parent)
{
    drawPosition = pDrawPosition;
    size = pSize;
}

void ClickableCardArray::rescale()
{
    CardVector cardArr;

    for(auto &clickableCard : clickableCards)
    {
        cardArr.push_back(clickableCard.data);
    }

    showCards(cardArr);
}

void ClickableCardArray::showCards(const CardVector &cardArr, CardStyleMap *cardStyles)
{
    int n = (int)cardArr.size();

    clickableCards.clear();
    clickableCards.resize(n); // ScaledQLabel::scaleFactor set to scalefactor

    for (auto i = 0; i < n; i++)
    {
        clickableCards[i].setParent(parentWidget());

        Card card = cardArr[i];
        string style = "";
        
        if (cardStyles)
        {
            style = (*cardStyles)[card];
        }

        if (style.empty())
        {
            style = "background-color: white; border: 2px solid"; // default style
        }

        clickableCards[i].setData(card, drawPosition, size, style);
        clickableCards[i].move(getCardPosition(i, n));
        clickableCards[i].showNormal();
    }
}

void ClickableCardArray::hideCards()
{
    clickableCards.clear();
}

QPoint ClickableCardArray::getCardPosition(int i, int n)
{
    // for dynamic positioning
    auto WIN_DIMENSIONS = getWindowDimensions();
    auto VERTICAL_SHIFT = getVerticalShift();
    auto HORIZONTAL_SHIFT = getHorizontalShift();
    auto CARDGAP = getCardGap();

    auto WIN_WIDTH = WIN_DIMENSIONS.first;
    auto WIN_HEIGHT = WIN_DIMENSIONS.second;
    auto TOTAL_WIDTH = size.width() /*card width*/ + (n - 1) * CARDGAP;

    switch (drawPosition)
    {
    case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
    case DRAW_POSITION_MAIN_WIDGET_CENTER:
    case DRAW_POSITION_MIDDLE_DLG_NEST:
    case DRAW_POSITION_NEST_DLG_TOP:
    case DRAW_POSITION_NEST_DLG_BOTTOM:
    case DRAW_POSITION_PARTNER_DLG:
        return {(WIN_WIDTH - TOTAL_WIDTH) / 2 + i * CARDGAP + HORIZONTAL_SHIFT,
                (WIN_HEIGHT) / 2 + VERTICAL_SHIFT};
    case DRAW_POSITION_MAIN_WIDGET_CENTER_BOTTOM:
        return {525, 375};
    case DRAW_POSITION_MAIN_WIDGET_CENTER_LEFT:
        return {325, 300};
    case DRAW_POSITION_MAIN_WIDGET_CENTER_TOP:
        return {525, 180};
    case DRAW_POSITION_MAIN_WIDGET_CENTER_RIGHT:
        return {655, 300};
    case DRAW_POSITION_MIDDLE_DLG_PARTNER:
        return {510, 260};
    case DRAW_POSITION_GAME_INFO_WIDGET:
        return {145, 35};
    case DRAW_POSITION_MESSAGE_BOX:
        return {75, 50};
    default: // not implemented
        return {0, 0};
    }
}

pair<int, int> ClickableCardArray::getWindowDimensions()
{
    switch (drawPosition)
    {
    case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
    case DRAW_POSITION_MAIN_WIDGET_CENTER:
        return make_pair(1200, 850);
    case DRAW_POSITION_MIDDLE_DLG_NEST:
        return make_pair(724, 435);
    case DRAW_POSITION_NEST_DLG_TOP:
    case DRAW_POSITION_NEST_DLG_BOTTOM:
        return make_pair(600, 300);
    case DRAW_POSITION_PARTNER_DLG:
        return make_pair(850, 300);
    default:
        return make_pair(0, 0); // dynamic positioning not implemented
    }
}

int ClickableCardArray::getVerticalShift()
{
    switch (drawPosition)
    {
    case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
        return 170;
    case DRAW_POSITION_MAIN_WIDGET_CENTER:
        return -100;
    case DRAW_POSITION_MIDDLE_DLG_NEST:
        return -200;
    case DRAW_POSITION_NEST_DLG_TOP:
        return -100;
    case DRAW_POSITION_NEST_DLG_BOTTOM:
        return 125;
    case DRAW_POSITION_PARTNER_DLG:
        return -40;
    default:
        return 0; // dynamic positioning not implemented
    }
}

int ClickableCardArray::getHorizontalShift()
{
    switch (drawPosition)
    {
    case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
    case DRAW_POSITION_MAIN_WIDGET_CENTER:
        return 45;
    case DRAW_POSITION_MIDDLE_DLG_NEST:
        return 230;
    case DRAW_POSITION_NEST_DLG_TOP:
    case DRAW_POSITION_NEST_DLG_BOTTOM:
        return 170;
    case DRAW_POSITION_PARTNER_DLG:
        return 0;
    default:
        return 0; // dynamic positioning not implemented
    }
}

int ClickableCardArray::getCardGap()
{
    switch (drawPosition)
    {
    case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
    case DRAW_POSITION_MAIN_WIDGET_CENTER:
    case DRAW_POSITION_MIDDLE_DLG_NEST:
    case DRAW_POSITION_NEST_DLG_TOP:
    case DRAW_POSITION_NEST_DLG_BOTTOM:
        return 40;
    case DRAW_POSITION_PARTNER_DLG:
        return 55;
    default:
        return 0; // only one card shown for this draw position
    }
}

QDialogWithClickableCardArray::QDialogWithClickableCardArray(bool pFixedSize, QWidget *parent) : ScaledQDialog(pFixedSize, parent)
{
}
