#include "gameController.h"
#include "nestDialog.h"
#include "utils.h"

NestDialog::NestDialog(QMainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                   QDialogWithClickableCardArray(parent),
                                                                   centerCards(DRAW_POSITION_NEST_DLG_TOP, SIZE_SMALL, this),
                                                                   bottomCardsPreview(DRAW_POSITION_NEST_DLG_BOTTOM, SIZE_SMALL, this)
{
    auto setupLabel = [this](ScaledQLabel *label, QString text, QPoint pos) {
        label->setParent(this);
        label->setFont(QFont("Times", 12));
        label->setText(text);
        label->move(pos);
    };

    auto setupPushButton = [this](ScaledQPushButton *pushButton, QString text, QPoint pos) {
        pushButton->setParent(this);
        pushButton->setText(text);
        pushButton->move(pos);
        pushButton->setFont(QFont("Times", 10));
    };

    setupLabel(&centerCardsLabel, "Middle cards (click to take)", {300, 10});
    centerCards.showCards(gc.nest);

    setupLabel(&bottomCardsPreviewLabel, "New hand (click to discard)", {300, 235});
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr);

    setupPushButton(&autoChooseNestButton, "Auto choose nest...", {220, 450});
    setupPushButton(&doneNestButton, "Done nest...", {480, 450});

    QObject::connect(&autoChooseNestButton, &QPushButton::pressed,
                     this, &NestDialog::autoChooseNestButtonPressed);

    QObject::connect(&doneNestButton, &QPushButton::pressed,
                     this, &NestDialog::doneNestButtonPressed);

    resize(911, 506);
    setWindowTitle("Nest Dialog");
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
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

    centerCards.showCards(gc.nest);
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr);
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

    centerCards.showCards(gc.nest);
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr);
}

void NestDialog::doneNestButtonPressed()
{
    if (gc.nest.size() != 5)
    {
        MessageBox msgBox;
        Utils::Ui::setupMessageBox(&msgBox, "Nest must have exactly 5 cards", "Nest problem");
        Utils::Ui::moveDialog(&msgBox, mainWindow, DIALOG_POSITION_CENTER);
        msgBox.exec();
    }
    else
    {
        accept();
    }
}