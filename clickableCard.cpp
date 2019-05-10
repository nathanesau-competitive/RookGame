#include "clickableCard.h"
#include "mainWindow.h"

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

void ClickableCard::setData(const Card &pData, int size)
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

    switch (size)
    {
    case SIZE_NORMAL:
        setPixmap(QPixmap(qImageName).scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    case SIZE_SMALL:
        setPixmap(QPixmap(qImageName).scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }

    setStyleSheet("background-color: white; border: 2px solid");
}

void ClickableCard::mousePressEvent(QMouseEvent *event)
{
    auto parentWidgetWithClickableCardArray = dynamic_cast<QDialogWithClickableCardArray*>(parent());

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
        currentClickableCard.setData(currentCard, size);
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
            return make_pair(700, 350);
        case DRAW_POSITION_PARTNER_DLG_ROW1:
        case DRAW_POSITION_PARTNER_DLG_ROW2:
        case DRAW_POSITION_PARTNER_DLG_ROW3:
        case DRAW_POSITION_PARTNER_DLG_ROW4:
        case DRAW_POSITION_PARTNER_DLG_ROW5:
            return make_pair(800, 650);
        default:
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
        case DRAW_POSITION_PARTNER_DLG_ROW1:
            return -150;
        case DRAW_POSITION_PARTNER_DLG_ROW2:
            return -40;
        case DRAW_POSITION_PARTNER_DLG_ROW3:
            return 70;
        case DRAW_POSITION_PARTNER_DLG_ROW4:
            return 180;
        case DRAW_POSITION_PARTNER_DLG_ROW5:
            return 290;
        default:
            return 0; // dynamic positioning not implemented
        }
    }();

    auto HORIZONTAL_SHIFT = [drawPosition]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_BOTTOM:
        case DRAW_POSITION_CENTER:
            return 0;
        case DRAW_POSITION_PARTNER_DLG_ROW1:
        case DRAW_POSITION_PARTNER_DLG_ROW2:
        case DRAW_POSITION_PARTNER_DLG_ROW3:
        case DRAW_POSITION_PARTNER_DLG_ROW4:
        case DRAW_POSITION_PARTNER_DLG_ROW5:
            return 100;
        default:
            return 0; // dynamic positioning not implemented
        }
    }();

    auto CARDGAP = [drawPosition]() {
        switch (drawPosition)
        {
        case DRAW_POSITION_BOTTOM:
        case DRAW_POSITION_CENTER:
            return 40;
        case DRAW_POSITION_PARTNER_DLG_ROW1:
        case DRAW_POSITION_PARTNER_DLG_ROW2:
        case DRAW_POSITION_PARTNER_DLG_ROW3:
        case DRAW_POSITION_PARTNER_DLG_ROW4:
        case DRAW_POSITION_PARTNER_DLG_ROW5:
            return 55;
        default:
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
    case DRAW_POSITION_PARTNER_DLG_ROW1:
    case DRAW_POSITION_PARTNER_DLG_ROW2:
    case DRAW_POSITION_PARTNER_DLG_ROW3:
    case DRAW_POSITION_PARTNER_DLG_ROW4:
    case DRAW_POSITION_PARTNER_DLG_ROW5:

        return {(WIN_WIDTH - TOTAL_WIDTH) / 2 + index * CARDGAP + WIDTH_OFFSET + HORIZONTAL_SHIFT,
                (WIN_HEIGHT) / 2 + NEST_HEIGHT_OFFSET + VERTICAL_SHIFT};

    case DRAW_POSITION_TRUMP_DLG: // only one card display (win_dim: 661x302)

        return {450,120};

    default: // not implemented

        return {0, 0};
    }
}

QDialogWithClickableCardArray::QDialogWithClickableCardArray(QWidget *parent) : QDialog(parent)
{
}
