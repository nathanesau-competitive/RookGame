#include <QBrush>
#include <QPainter>
#include <QTransform>

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

void ClickableCard::setData(const Card &pData, int drawPosition, QSize size)
{
    data = pData;

    string valueString = [&]() {
        switch (data.value)
        {
        case VALUE_ROOK:
            return "rook";
        case VALUE_1:
            return "1";
        case VALUE_2:
            return "2";
        case VALUE_3:
            return "3";
        case VALUE_4:
            return "4";
        case VALUE_5:
            return "5";
        case VALUE_6:
            return "6";
        case VALUE_7:
            return "7";
        case VALUE_8:
            return "8";
        case VALUE_9:
            return "9";
        case VALUE_10:
            return "10";
        case VALUE_11:
            return "11";
        case VALUE_12:
            return "12";
        case VALUE_13:
            return "13";
        case VALUE_14:
            return "14";
        default: // VALUE_UNDEFINED
            return "";
        }
    }();

    string suitString = [&]() {
        switch (data.suit)
        {
        case SUIT_BLACK:
            return "black";
        case SUIT_GREEN:
            return "green";
        case SUIT_RED:
            return "red";
        case SUIT_YELLOW:
            return "yellow";
        case SUIT_SPECIAL:
            return "";
        default: // SUIT_UNDEFINED
            return "blank";
        }
    }();

    string imageName = ":" + valueString + suitString + ".gif";
    QString qImageName = QString::fromStdString(imageName);

    auto transform = [](const int drawPosition) -> QTransform {
        QTransform transform;
        switch (drawPosition)
        {
        case DRAW_POSITION_MAIN_WIDGET_CENTER_LEFT:
            transform.rotate(90);
            break;
        case DRAW_POSITION_MAIN_WIDGET_CENTER_TOP:
            transform.rotate(180);
            break;
        case DRAW_POSITION_MAIN_WIDGET_CENTER_RIGHT:
            transform.rotate(270);
            break;
        default:
            // no rotation
            break;
        }

        return transform;
    }(drawPosition);

    auto setPixmap = [this](const QString &fileName, const QSize &size, const QTransform &transform) {
        auto pixmap = QPixmap(fileName);
        this->setPixmap(pixmap, size, transform);
    };

    setPixmap(qImageName, size, transform);
    setStyleSheet("background-color: white; border: 2px solid");
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

ClickableCardArray::ClickableCardArray(int pDrawPosition, QSize pSize, QDialogWithClickableCardArray *pParent) :
    parent(pParent)
{
    drawPosition = pDrawPosition;
    size = pSize;
}

void ClickableCardArray::showCards(const vector<Card> &cardArr)
{
    int n = (int)cardArr.size();

    clickableCards.clear();
    clickableCards.resize(n);

    for (auto i = 0; i < n; i++)
    {
        clickableCards[i].setParent(parent);
        clickableCards[i].setData(cardArr[i], drawPosition, size);
        clickableCards[i].move(getCardPosition(i, n));
        clickableCards[i].showNormal();
    }
}

void ClickableCardArray::hideCards()
{
    for (auto &card : clickableCards)
    {
        card.hide();
    }
}

QPoint ClickableCardArray::getCardPosition(int i, int n)
{
    auto WIN_DIMENSIONS = [this]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
            return make_pair(1200, 850);
        case DRAW_POSITION_MIDDLE_DLG_NEST:
            return make_pair(724, 435);
        case DRAW_POSITION_NEST_DLG_TOP:
        case DRAW_POSITION_NEST_DLG_BOTTOM:
            return make_pair(600, 300);
        case DRAW_POSITION_PARTNER_DLG:
            return make_pair(800, 300);
        default:
            return make_pair(0, 0); // dynamic positioning not implemented
        }
    }();

    // shift from center of screen
    auto VERTICAL_SHIFT = [this]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
            return 170;
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
    }();

    auto HORIZONTAL_SHIFT = [this]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
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
    }();

    auto CARDHEIGHT = size.width();

    auto CARDGAP = [this]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
        case DRAW_POSITION_MIDDLE_DLG_NEST:
        case DRAW_POSITION_NEST_DLG_TOP:
        case DRAW_POSITION_NEST_DLG_BOTTOM:
            return 40;
        case DRAW_POSITION_PARTNER_DLG:
            return 55;
        default:
            return 0; // only one card shown for this draw position
        }
    }();

    const int WIN_WIDTH = WIN_DIMENSIONS.first;
    const int WIN_HEIGHT = WIN_DIMENSIONS.second;
    const int TOTAL_WIDTH = CARDHEIGHT + (n - 1) * CARDGAP;

    switch (drawPosition)
    {
    case DRAW_POSITION_MAIN_WIDGET_BOTTOM:
    case DRAW_POSITION_MIDDLE_DLG_NEST:
    case DRAW_POSITION_NEST_DLG_TOP:
    case DRAW_POSITION_NEST_DLG_BOTTOM:
    case DRAW_POSITION_PARTNER_DLG:
        return {(WIN_WIDTH - TOTAL_WIDTH) / 2 + i * CARDGAP + HORIZONTAL_SHIFT,
                (WIN_HEIGHT) / 2 + VERTICAL_SHIFT};
    case DRAW_POSITION_MAIN_WIDGET_CENTER_BOTTOM:
        return {500, 375};
    case DRAW_POSITION_MAIN_WIDGET_CENTER_LEFT:
        return {300, 300};
    case DRAW_POSITION_MAIN_WIDGET_CENTER_TOP:
        return {500, 180};
    case DRAW_POSITION_MAIN_WIDGET_CENTER_RIGHT:
        return {630, 300};
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

QDialogWithClickableCardArray::QDialogWithClickableCardArray(QWidget *parent) : ScaledQDialog(parent)
{
}
