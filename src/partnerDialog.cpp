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
                                                                     QDialogWithClickableCardArray(parent),
                                                                     centerCards(DRAW_POSITION_PARTNER_DLG, SIZE_TINY, this)
{
    auto splitCardArray = [](vector<vector<Card> *> &suitArrays, vector<Card> &cardArr) {
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
    vector<const vector<Card> *> cardArrays = {&gc.playerArr[PLAYER_2].cardArr, &gc.playerArr[PLAYER_3].cardArr,
                                               &gc.playerArr[PLAYER_4].cardArr, &gc.nest};
    vector<Card> aggregateCardArr = Utils::Game::getAggregateCardArray(cardArrays);
    Utils::Game::sortCardArray(aggregateCardArr);

    vector<vector<Card> *> suitArrays = {&blackCards, &greenCards, &redCards, &yellowCards, &wildCards};
    splitCardArray(suitArrays, aggregateCardArr);

    auto setupPartnerLabel = [this](PartnerDialogLabel &label, QString text, QString style, QPoint pos) {
        label.setFont(QFont("Times", 12));
        label.setText(text);
        label.setStyleSheet(style);
        label.setParent(this);
        label.move(pos);
        label.setAlignment(Qt::AlignCenter);
        label.resize(50, 25);
    };

    setupPartnerLabel(redLabel, "Red", "background-color: red; border: 2px solid", QPoint(25, 25));
    setupPartnerLabel(blackLabel, "Black", "background-color: black; color: white; border: 2px solid", QPoint(75, 25));
    setupPartnerLabel(greenLabel, "Green", "background-color: green; border: 2px solid", QPoint(125, 25));
    setupPartnerLabel(yellowLabel, "Yellow", "background-color: yellow; border: 2px solid", QPoint(175, 25));
    setupPartnerLabel(wildLabel, "Wild", "background-color: white; border:2px solid", QPoint(225, 25));

    cancelButton.setParent(this);
    cancelButton.setText("Cancel");
    cancelButton.setFont(QFont("Times", 10));
    cancelButton.resize(50, 25);
    cancelButton.move({700, 250});

    QObject::connect(&cancelButton, &QPushButton::pressed, this, &PartnerDialog::accept);

    setWindowTitle("Click partner card...");
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setGeometry(QRect(0, 0, 800, 300));
}

PartnerDialog::~PartnerDialog()
{
    // todo
}

void PartnerDialog::onPartnerLabelClicked(PartnerDialogLabel *label)
{
    string text = label->text().toStdString();

    if (text == "Black")
    {
        centerCards.showCards(blackCards);
    }
    else if (text == "Green")
    {
        centerCards.showCards(greenCards);
    }
    else if (text == "Red")
    {
        centerCards.showCards(redCards);
    }
    else if (text == "Yellow")
    {
        centerCards.showCards(yellowCards);
    }
    else if (text == "Wild")
    {
        centerCards.showCards(wildCards);
    }
}

void PartnerDialog::onCardClicked(ClickableCard *clickableCard)
{
    cardSelected.suit = clickableCard->data.suit;
    cardSelected.value = clickableCard->data.value;

    accept();
}
