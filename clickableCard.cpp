#include "clickableCard.h"
#include "mainWindow.h"

#include <QTransform>

ClickableCard::ClickableCard(QWidget *parent) : QLabel(parent)
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

void ClickableCard::setData(const Card &pData, const int drawPosition, int size)
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

    auto transform = [](const int drawPosition) -> QTransform
    {
        QTransform transform;
        switch(drawPosition)
        {
        case DRAW_POSITION_CARD_PLAYED_LEFT:
            transform.rotate(90);
            break;
        case DRAW_POSITION_CARD_PLAYED_TOP:
            transform.rotate(180);
            break;
        case DRAW_POSITION_CARD_PLAYED_RIGHT:
            transform.rotate(270);
            break;
        default:
            // no rotation
            break;
        }

        return transform;
    } (drawPosition);

    // todo: use draw position to rotate
    switch (size)
    {
    case SIZE_NORMAL:
        setPixmap(QPixmap(qImageName).scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation).transformed(transform));
        break;
    case SIZE_SMALL:
        setPixmap(QPixmap(qImageName).scaled(135, 135, Qt::KeepAspectRatio, Qt::SmoothTransformation).transformed(transform));
        break;
    case SIZE_TINY:
        setPixmap(QPixmap(qImageName).scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation).transformed(transform));
        break;
    }

    setStyleSheet("background-color: white; border: 2px solid");
}

void ClickableCard::mousePressEvent(QMouseEvent *event)
{
    auto parentWidgetWithClickableCardArray = dynamic_cast<QDialogWithClickableCardArray *>(parent());

    parentWidgetWithClickableCardArray->onCardClicked(this);
}

ClickableCardArray::ClickableCardArray(QWidget *parent) : QObject(parent)
{
}

void ClickableCardArray::showCards(const vector<Card> &cardArr, const int drawPosition, const int size)
{
    int numCards = (int)cardArr.size();

    clickableCards.clear();
    clickableCards.resize(numCards);

    auto parentWidget = dynamic_cast<QWidget *>(parent());

    for (auto i = 0; i < numCards; i++)
    {
        auto &currentCard = cardArr[i];
        auto &currentClickableCard = clickableCards[i];

        currentClickableCard.setParent(parentWidget);
        currentClickableCard.setData(currentCard, drawPosition, size);
        currentClickableCard.move(getCardPosition(numCards, i, drawPosition));
        currentClickableCard.showNormal();
    }
}

void ClickableCardArray::hideCards()
{
    for (auto &card : clickableCards)
    {
        card.hide();
    }
}

QPoint ClickableCardArray::getCardPosition(int n, int index, const int drawPosition)
{
    auto WIN_DIMENSIONS = [drawPosition]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_BOTTOM:
            return make_pair(1200, 850);
        case DRAW_POSITION_CENTER:
        case DRAW_POSITION_CENTER_PREVIEW:
            return make_pair(600, 300);
        case DRAW_POSITION_PARTNER_DLG_ROW1:
        case DRAW_POSITION_PARTNER_DLG_ROW2:
        case DRAW_POSITION_PARTNER_DLG_ROW3:
            return make_pair(1000, 400);
        default:
            // DRAW_POSITION_TOP_LEFT
            // ...
            return make_pair(0, 0); // dynamic positioning not implemented
        }
    }();

    // shift from center of screen
    auto VERTICAL_SHIFT = [drawPosition]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_BOTTOM:
            return 0;
        case DRAW_POSITION_CENTER:
            return 0;
        case DRAW_POSITION_CENTER_PREVIEW:
            return 225;
        case DRAW_POSITION_PARTNER_DLG_ROW1:
            return -50;
        case DRAW_POSITION_PARTNER_DLG_ROW2:
            return 60;
        case DRAW_POSITION_PARTNER_DLG_ROW3:
            return 170;
        default:
            // DRAW_POSITION_TOP_LEFT
            // ...
            return 0; // dynamic positioning not implemented
        }
    }();

    auto HORIZONTAL_SHIFT = [drawPosition]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_BOTTOM:
            return 90;
        case DRAW_POSITION_CENTER:
        case DRAW_POSITION_CENTER_PREVIEW:
            return 170;
        case DRAW_POSITION_PARTNER_DLG_ROW1:
        case DRAW_POSITION_PARTNER_DLG_ROW2:
        case DRAW_POSITION_PARTNER_DLG_ROW3:
            return 100;
        default:
            // DRAW_POSITION_TOP_LEFT
            // ...
            return 0; // dynamic positioning not implemented
        }
    }();

    auto CARDGAP = [drawPosition]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_BOTTOM:
        case DRAW_POSITION_CENTER:
        case DRAW_POSITION_CENTER_PREVIEW:
            return 40;
        case DRAW_POSITION_PARTNER_DLG_ROW1:
        case DRAW_POSITION_PARTNER_DLG_ROW2:
        case DRAW_POSITION_PARTNER_DLG_ROW3:
            return 55;
        default:
            // DRAW_POSITION_TOP_LEFT
            // ...
            return 0; // dynamic positioning not implemented
        }
    }();

    const int WIN_WIDTH = WIN_DIMENSIONS.first;
    const int WIN_HEIGHT = WIN_DIMENSIONS.second;

    const int WIDTH_OFFSET = 25;
    const int HEIGHT_OFFSET = -10; // NOT USED

    const int BOTTOM_BORDER_GAP = 90;
    const int TOP_BORDER_GAP = 20;   // NOT USED
    const int LEFT_BORDER_GAP = 20;  // NOT USED
    const int RIGHT_BORDER_GAP = 50; // NOT USED

    const int CARDHEIGHT = 180;
    const int CARDWIDTH = 180; // NOT USED

    const int NEST_HEIGHT_OFFSET = -100;

    const int TOTAL_WIDTH = CARDHEIGHT + (n - 1) * CARDGAP;

    switch (drawPosition)
    {
    case DRAW_POSITION_BOTTOM:
        return {(WIN_WIDTH - TOTAL_WIDTH) / 2 + index * CARDGAP + WIDTH_OFFSET,
                WIN_HEIGHT - CARDHEIGHT - BOTTOM_BORDER_GAP};
    case DRAW_POSITION_CENTER:
    case DRAW_POSITION_CENTER_PREVIEW:
    case DRAW_POSITION_PARTNER_DLG_ROW1:
    case DRAW_POSITION_PARTNER_DLG_ROW2:
    case DRAW_POSITION_PARTNER_DLG_ROW3:
        return {(WIN_WIDTH - TOTAL_WIDTH) / 2 + index * CARDGAP + WIDTH_OFFSET + HORIZONTAL_SHIFT,
                (WIN_HEIGHT) / 2 + NEST_HEIGHT_OFFSET + VERTICAL_SHIFT};
    case DRAW_POSITION_TRUMP_DLG: // only one card display (win_dim: 661x302)
        return {450, 120};
    case DRAW_POSITION_TOP_LEFT: // only one card display (win_dim: 1200x850)
        return {50, 35};
    case DRAW_POSITION_CARD_PLAYED_BOTTOM:
        return {500, 375};
    case DRAW_POSITION_CARD_PLAYED_LEFT:
        return {300, 300};
    case DRAW_POSITION_CARD_PLAYED_TOP:
        return {500, 180};
    case DRAW_POSITION_CARD_PLAYED_RIGHT:
        return {630, 300};
    default: // not implemented
        return {0, 0};
    }
}

QDialogWithClickableCardArray::QDialogWithClickableCardArray(QWidget *parent) : QDialog(parent)
{
}
