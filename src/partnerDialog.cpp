#include "gameController.h"
#include "partnerDialog.h"
#include "utils.h"

PartnerDialogLabel::PartnerDialogLabel(PartnerDialog *parent) : ScaledQLabel(parent)
{
}

void PartnerDialogLabel::mousePressEvent(QMouseEvent *event)
{
    PartnerDialog *parentDialog = dynamic_cast<PartnerDialog *>(parent());

    parentDialog->onPartnerLabelClicked(this);
}

PartnerDialog::PartnerDialog(Card &pCardSelected, QWidget *parent) : cardSelected(pCardSelected),
                                                                     QDialogWithClickableCardArray(true, parent)
{
    setupCardArrays();

    auto setupPartnerLabel = [this](PartnerDialogLabel *label, QString text, QString style, QPoint pos) {
        label->setFont(QFont("Times", 12));
        label->setText(text);
        label->setStyleSheet(style);
        label->setParent(this);
        label->move(pos);
        label->setAlignment(Qt::AlignCenter);
        label->resize(50, 25);
    };

    centerCards = new ClickableCardArray(DRAW_POSITION_PARTNER_DLG, SIZE_TINY, this);

    redLabel = new PartnerDialogLabel;
    setupPartnerLabel(redLabel, "Red", "background-color: red; border: 2px solid", QPoint(25, 25));

    blackLabel = new PartnerDialogLabel;
    setupPartnerLabel(blackLabel, "Black", "background-color: black; color: white; border: 2px solid", QPoint(75, 25));

    greenLabel = new PartnerDialogLabel;
    setupPartnerLabel(greenLabel, "Green", "background-color: green; border: 2px solid", QPoint(125, 25));

    yellowLabel = new PartnerDialogLabel;
    setupPartnerLabel(yellowLabel, "Yellow", "background-color: yellow; border: 2px solid", QPoint(175, 25));

    wildLabel = new PartnerDialogLabel;
    setupPartnerLabel(wildLabel, "Wild", "background-color: white; border:2px solid", QPoint(225, 25));

    cancelButton = new ScaledQPushButton;
    cancelButton->setParent(this);
    cancelButton->setText("Cancel");
    cancelButton->setFont(QFont("Times", 10));
    cancelButton->resize(50, 25);
    cancelButton->move({700, 250});

    QObject::connect(cancelButton, &QPushButton::pressed, this, &QDialog::accept);

    setWindowTitle("Click partner card...");
    setWindowIcon(QIcon(":rookicon.gif"));
    setGeometry(QRect(0, 0, 850, 300));
}

void PartnerDialog::rescale()
{
    updateScaleFactor();
    setGeometry(geometry());

    for (auto label : vector<PartnerDialogLabel *>{blackLabel, greenLabel, redLabel, yellowLabel, wildLabel})
        label->rescale();

    for (auto button : vector<ScaledQPushButton *>{cancelButton})
        button->rescale();

    for (auto clickableCardArray : vector<ClickableCardArray *>{centerCards})
        clickableCardArray->rescale();
}

void PartnerDialog::onPartnerLabelClicked(PartnerDialogLabel *label)
{
    string text = label->text().toStdString();

    if (text == "Black")
    {
        centerCards->showCards(blackCards);
    }
    else if (text == "Green")
    {
        centerCards->showCards(greenCards);
    }
    else if (text == "Red")
    {
        centerCards->showCards(redCards);
    }
    else if (text == "Yellow")
    {
        centerCards->showCards(yellowCards);
    }
    else if (text == "Wild")
    {
        centerCards->showCards(wildCards);
    }
}

void PartnerDialog::onCardClicked(ClickableCard *clickableCard)
{
    cardSelected.suit = clickableCard->data.suit;
    cardSelected.value = clickableCard->data.value;

    QDialog::accept();
}

void PartnerDialog::onCardHoverEnter(ClickableCard *clickableCard)
{
    // do nothing
}

void PartnerDialog::onCardHoverLeave(ClickableCard *clickableCard)
{
    // do nothing
}

void PartnerDialog::setupCardArrays()
{
    auto splitCardArray = [](vector<CardVector *> &suitArrays, CardVector &cardArr) {
        for (auto card : cardArr)
        {
            if (card.suit == SUIT_BLACK)
                suitArrays[SUIT_BLACK]->push_back(card);
            else if (card.suit == SUIT_GREEN)
                suitArrays[SUIT_GREEN]->push_back(card);
            else if (card.suit == SUIT_RED)
                suitArrays[SUIT_RED]->push_back(card);
            else if (card.suit == SUIT_YELLOW)
                suitArrays[SUIT_YELLOW]->push_back(card);
            else if (card.suit == SUIT_SPECIAL)
                suitArrays[SUIT_SPECIAL]->push_back(card);
        }
    };

    // don't allow user to pick themself as partner
    vector<const CardVector *> cardArrays = {&gc.playerArr[PLAYER_2].cardArr, &gc.playerArr[PLAYER_3].cardArr,
                                             &gc.playerArr[PLAYER_4].cardArr};
    CardVector aggregateCardArr;
    aggregateCardArr.append(cardArrays);
    aggregateCardArr.sort();

    vector<CardVector *> suitArrays = {&blackCards, &greenCards, &redCards, &yellowCards, &wildCards};
    splitCardArray(suitArrays, aggregateCardArr);
}