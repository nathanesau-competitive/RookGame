#include <QPushButton>
#include <QObject>
#include <QMessageBox>
#include <string>

#include "gameController.h"
#include "mainWindow.h"
#include "middleDialog.h"
#include "utils.h"

using namespace std;

MiddleDialog::MiddleDialog(int &pTrumpSuitSelected, Card &pPartnerCardSelected,
                           MainWidget *pMainWidget, QMainWindow *pMainWindow, QWidget *parent) : trumpSuitSelected(pTrumpSuitSelected),
                                                                                                 partnerCardSelected(pPartnerCardSelected),
                                                                                                 mainWidget(pMainWidget),
                                                                                                 mainWindow(pMainWindow),
                                                                                                 QDialogWithClickableCardArray(parent)
{
    ui.setupUi(this);

    topRightCards.setParent(this);
    topRightCards.showCards(gc.nest, DRAW_POSITION_MIDDLE_DLG_NEST, SIZE_TINY);

    bottomRightCards.setParent(this);
    bottomRightCards.showCards({Card(SUIT_UNDEFINED, VALUE_UNDEFINED)}, DRAW_POSITION_MIDDLE_DLG_PARTNER, SIZE_TINY);

    QObject::connect(ui.selectNestButton, &QPushButton::pressed,
                     this, &MiddleDialog::selectNestButtonPressed);

    QObject::connect(ui.autoSelectNestButton, &QPushButton::pressed,
                     this, &MiddleDialog::autoSelectNestButtonPressed);

    QObject::connect(ui.selectTrumpButton, &QPushButton::pressed,
                     this, &MiddleDialog::selectTrumpButtonPressed);

    QObject::connect(ui.autoSelectTrumpButton, &QPushButton::pressed,
                     this, &MiddleDialog::autoSelectTrumpButtonPressed);

    QObject::connect(ui.selectPartnerButton, &QPushButton::pressed,
                     this, &MiddleDialog::selectPartnerButtonPressed);

    QObject::connect(ui.autoSelectPartnerButton, &QPushButton::pressed,
                     this, &MiddleDialog::autoSelectPartnerButtonPressed);

    QObject::connect(ui.okButton, &QPushButton::pressed,
                     this, &MiddleDialog::okButtonPressed);

    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

MiddleDialog::~MiddleDialog()
{
    // todo
}

void MiddleDialog::onCardClicked(ClickableCard *clickableCard)
{
    // do nothing
}

void MiddleDialog::selectNestButtonPressed()
{
    NestDialog nestDlg(mainWindow);
    Utils::Ui::moveDialogToCenter(&nestDlg, mainWindow, {-40, 0});

    if (!nestDlg.exec())
    {
        qFatal("Problem executing nest dialog");
        return;
    }
}

void MiddleDialog::autoSelectNestButtonPressed()
{
    NestDialog::autoChooseNest();

    topRightCards.showCards(gc.nest, DRAW_POSITION_MIDDLE_DLG_NEST, SIZE_TINY);
    mainWidget->showBottomCards(gc.playerArr[PLAYER_1].cardArr);
}

void MiddleDialog::selectTrumpButtonPressed()
{
    TrumpDialog trumpDlg(trumpSuitSelected);
    Utils::Ui::moveDialogToCenter(&trumpDlg, mainWindow);

    if (!trumpDlg.exec())
    {
        qFatal("Problem executing trump dialog");
        return;
    }

    setupTrumpLabel(trumpSuitSelected);
}

void MiddleDialog::autoSelectTrumpButtonPressed()
{
    // choose suit which player has most of as trump
    vector<SuitInfo> suitInfoArr = Utils::Game::getSuitInfoArray(gc.playerArr[PLAYER_1].cardArr);

    trumpSuitSelected = suitInfoArr[0].suit != SUIT_SPECIAL ? suitInfoArr[0].suit
                                                            : suitInfoArr[1].suit;
    setupTrumpLabel(trumpSuitSelected);
}

void MiddleDialog::selectPartnerButtonPressed()
{
    PartnerDialog partnerDlg(partnerCardSelected);
    Utils::Ui::moveDialogToCenter(&partnerDlg, mainWindow, {-100, 0});

    if (!partnerDlg.exec())
    {
        qFatal("Problem executing partner dialog");
        return;
    }

    bottomRightCards.showCards({partnerCardSelected}, DRAW_POSITION_MIDDLE_DLG_PARTNER, SIZE_TINY);
}

void MiddleDialog::autoSelectPartnerButtonPressed()
{
    // choose highest card NOT in players hand
    //      of suit which player has most of

    vector<const vector<Card> *> cardArrays = {&gc.playerArr[PLAYER_2].cardArr, &gc.playerArr[PLAYER_3].cardArr, &gc.playerArr[PLAYER_4].cardArr, &gc.nest};
    vector<Card> cardArr = Utils::Game::getAggregateCardArray(cardArrays);
    Utils::Game::sortCardArray(cardArr);

    auto suitInfoArr = Utils::Game::getSuitInfoArray(gc.playerArr[PLAYER_1].cardArr);

    auto bestSuit = suitInfoArr[0].suit != SUIT_SPECIAL ? suitInfoArr[0].suit
                                                        : suitInfoArr[1].suit;

    Card bestCard(bestSuit, VALUE_1);

    for (auto &card : cardArr)
    {
        if (card.suit != bestSuit)
            continue;

        if (card.value > bestCard.value)
        {
            bestCard = card;
        }
    }

    if (bestCard != Card(bestSuit, VALUE_1)) // found a good card
    {
        partnerCardSelected = bestCard;
        bottomRightCards.showCards({partnerCardSelected}, DRAW_POSITION_MIDDLE_DLG_PARTNER, SIZE_TINY);
    }
}

void MiddleDialog::okButtonPressed()
{
    accept();
}

void MiddleDialog::setupTrumpLabel(int suit)
{
    auto trumpLabel = ui.trumpLabel;

    switch (suit)
    {
    case SUIT_BLACK:
        trumpLabel->setStyleSheet("background-color: black; color: white");
        trumpLabel->setText("Black");
        break;
    case SUIT_GREEN:
        trumpLabel->setStyleSheet("background-color: green");
        trumpLabel->setText("Green");
        break;
    case SUIT_RED:
        trumpLabel->setStyleSheet("background-color: red");
        trumpLabel->setText("Red");
        break;
    case SUIT_YELLOW:
        trumpLabel->setStyleSheet("background-color: yellow");
        trumpLabel->setText("Yellow");
        break;
    default:
        trumpLabel->setStyleSheet(""); // empty style
        trumpLabel->setText("No Trump Selected");
        break;
    }
}

NestDialog::NestDialog(QMainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                   QDialogWithClickableCardArray(parent)
{
    auto setupLabel = [this](QLabel *label, QString text, QPoint pos) {
        label->setParent(this);
        label->setFont(QFont("Times", 12));
        label->setText(text);
        label->move(pos);
    };

    auto setupPushButton = [this](QPushButton *pushButton, QString text, QPoint pos) {
        pushButton->setParent(this);
        pushButton->setText(text);
        pushButton->move(pos);
    };

    setupLabel(&centerCardsLabel, "Middle cards (click to take)", {300, 10});
    centerCards.setParent(this);
    centerCards.showCards(gc.nest, DRAW_POSITION_NEST_DLG_TOP, SIZE_SMALL);

    setupLabel(&bottomCardsPreviewLabel, "New hand (click to discard)", {300, 235});
    bottomCardsPreview.setParent(this);
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr, DRAW_POSITION_NEST_DLG_BOTTOM, SIZE_SMALL);

    setupPushButton(&autoChooseNestButton, "Auto choose nest...", {220, 450});
    setupPushButton(&doneNestButton, "Done nest...", {480, 450});

    QObject::connect(&autoChooseNestButton, &QPushButton::pressed,
                     this, &NestDialog::autoChooseNestButtonPressed);

    QObject::connect(&doneNestButton, &QPushButton::pressed,
                     this, &NestDialog::doneNestButtonPressed);

    setWindowTitle("Nest Dialog");
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
    setMaximumSize(911, 506);
    setFixedSize(maximumSize());
}

NestDialog::~NestDialog()
{
    // todo
}

void NestDialog::onCardClicked(ClickableCard *clickableCard)
{
    Card card = clickableCard->data;

    auto &nest = gc.nest;
    auto &hand = gc.playerArr[PLAYER_1].cardArr;

    auto nestIt = std::find(nest.begin(), nest.end(), card);
    auto handIt = std::find(hand.begin(), hand.end(), card);

    if (nestIt != nest.end())
    {
        nest.erase(nestIt);

        hand.push_back(card);
        Utils::Game::sortCardArray(hand);
    }
    else // handIt != hand.end()
    {
        hand.erase(handIt);
        nest.push_back(card);
        Utils::Game::sortCardArray(nest);
    }

    centerCards.showCards(gc.nest, DRAW_POSITION_NEST_DLG_TOP, SIZE_SMALL);
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr, DRAW_POSITION_NEST_DLG_BOTTOM, SIZE_SMALL);
}

void NestDialog::autoChooseNest()
{
    for (auto card : gc.nest)
    {
        gc.playerArr[PLAYER_1].cardArr.push_back(card);
    }

    gc.nest.clear();

    Utils::Game::sortCardArray(gc.playerArr[PLAYER_1].cardArr);

    // return cards which were removed
    auto removeCards = [](vector<Card> &cardArr, int suit, int count) {
        vector<Card> cardsRemoved;

        if (count > 0)
        {
            for (auto It = cardArr.begin(); It != cardArr.end();)
            {
                if (It->suit == suit)
                {
                    cardsRemoved.push_back(*It);
                    It = cardArr.erase(It);
                }
                else
                {
                    It++;
                }

                if (cardsRemoved.size() == count)
                {
                    break;
                }
            }
        }

        return cardsRemoved;
    };

    auto suitInfoArr = Utils::Game::getSuitInfoArray(gc.playerArr[PLAYER_1].cardArr);

    int cardsToRemove = 5;

    while (cardsToRemove > 0) // discard worst cards to nest
    {
        auto It = --suitInfoArr.end();

        if (It->count > 0)
        {
            int cardsToRemoveThisSuit = min(It->count, cardsToRemove);

            vector<Card> cardsRemoved = removeCards(gc.playerArr[PLAYER_1].cardArr, It->suit, cardsToRemoveThisSuit);
            cardsToRemove -= cardsToRemoveThisSuit;

            for (auto &card : cardsRemoved)
            {
                gc.nest.push_back(card);
            }
        }

        suitInfoArr.erase(It);
    }
}

void NestDialog::autoChooseNestButtonPressed()
{
    NestDialog::autoChooseNest();

    centerCards.showCards(gc.nest, DRAW_POSITION_NEST_DLG_TOP, SIZE_SMALL);
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr, DRAW_POSITION_NEST_DLG_BOTTOM, SIZE_SMALL);
}

void NestDialog::doneNestButtonPressed()
{
    if (gc.nest.size() != 5)
    {
        MessageBox msgBox;
        Utils::Ui::setupMessageBox(&msgBox, "Nest must have exactly 5 cards", "Nest problem");
        Utils::Ui::moveDialogToCenter(&msgBox, mainWindow);
        msgBox.exec();
    }
    else
    {
        accept();
    }
}

TrumpDialog::TrumpDialog(int &pSuitSelected, QWidget *parent) : suitSelected(pSuitSelected), QDialog(parent)
{
    auto setupTrumpLabel = [this](TrumpLabel &label, QString text, QString style, QPoint pos) {
        label.setFont(QFont("Times", 12));
        label.setText(text);
        label.setStyleSheet(style);
        label.setParent(this);
        label.move(pos);
        label.setAlignment(Qt::AlignCenter);
    };

    setupTrumpLabel(redLabel, "Red", "background-color: red", QPoint(25, 25));
    setupTrumpLabel(blackLabel, "Black", "background-color: black; color: white", QPoint(25, 75));
    setupTrumpLabel(greenLabel, "Green", "background-color: green", QPoint(25, 125));
    setupTrumpLabel(yellowLabel, "Yellow", "background-color: yellow", QPoint(25, 175));

    setGeometry(0, 0, 600, 250);
    setMaximumSize(QSize(600, 250));
    setFixedSize(maximumSize());
    setWindowTitle("Choose Trump Suit...");
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

TrumpDialog::~TrumpDialog()
{
    // todo
}

void TrumpDialog::onTrumpLabelClicked(TrumpLabel *label)
{
    string text = label->text().toStdString();

    if (text == "Black")
    {
        suitSelected = SUIT_BLACK;
    }
    else if (text == "Green")
    {
        suitSelected = SUIT_GREEN;
    }
    else if (text == "Red")
    {
        suitSelected = SUIT_RED;
    }
    else if (text == "Yellow")
    {
        suitSelected = SUIT_YELLOW;
    }

    accept();
}

PartnerDialog::PartnerDialog(Card &pCardSelected, QWidget *parent) : cardSelected(pCardSelected),
                                                                     QDialogWithClickableCardArray(parent)
{
    blackCards.setParent(this);
    greenCards.setParent(this);
    redCards.setParent(this);
    yellowCards.setParent(this);
    specialCards.setParent(this);

    setWindowTitle("Click partner card...");
    setWindowIcon(QIcon(":rookicon.gif"));
    setGeometry(0, 0, 1000, 400);
    setMaximumSize(QSize(1000, 400));
    setFixedSize(maximumSize());

    vector<Card> row1Arr;
    vector<Card> row2Arr;
    vector<Card> row3Arr;
    vector<vector<Card> *> rowArrays = {&row1Arr, &row2Arr, &row3Arr};

    auto splitCardArray = [](vector<vector<Card> *> &outCardArrays, vector<Card> &inCardArr) {
        int subsetSize = (int)ceil((double)inCardArr.size() / (double)outCardArrays.size());

        for (int i = 0; i < outCardArrays.size(); i++)
        {
            auto outCardArr = outCardArrays[i];

            for (int j = 0; j < subsetSize; j++)
            {
                outCardArr->push_back(inCardArr.front());
                inCardArr.erase(inCardArr.begin());

                if (inCardArr.empty())
                {
                    return;
                }
            }
        }
    };

    vector<const vector<Card> *> cardArrays = {&gc.playerArr[PLAYER_2].cardArr, &gc.playerArr[PLAYER_3].cardArr, &gc.playerArr[PLAYER_4].cardArr, &gc.nest};
    vector<Card> cardArr = Utils::Game::getAggregateCardArray(cardArrays);

    Utils::Game::sortCardArray(cardArr);
    splitCardArray(rowArrays, cardArr);

    blackCards.showCards(row1Arr, DRAW_POSITION_PARTNER_DLG_ROW1, SIZE_TINY);
    greenCards.showCards(row2Arr, DRAW_POSITION_PARTNER_DLG_ROW2, SIZE_TINY);
    redCards.showCards(row3Arr, DRAW_POSITION_PARTNER_DLG_ROW3, SIZE_TINY);
}

PartnerDialog::~PartnerDialog()
{
    // todo
}

void PartnerDialog::onCardClicked(ClickableCard *clickableCard)
{
    cardSelected.suit = clickableCard->data.suit;
    cardSelected.value = clickableCard->data.value;

    accept();
}
