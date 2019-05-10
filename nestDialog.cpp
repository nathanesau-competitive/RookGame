#include "nestDialog.h"
#include "gameController.h"
#include "mainWindow.h"
#include "ui_NestDialog.h"

NestDialog::NestDialog(QWidget *parent) : QDialogWithClickableCardArray(parent),
                                          ui(new Ui::NestDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->autoChooseMiddleButton, &QPushButton::pressed,
                     this, &NestDialog::autoChooseMiddleButtonPressed);

    QObject::connect(ui->doneMiddleButton, &QPushButton::pressed,
                     this, &NestDialog::doneMiddleButtonPressed);

    centerCardsLabel.setParent(this);
    centerCardsLabel.setText("Middle cards (click to take)");
    centerCardsLabel.setFont(QFont("Times", 12));
    centerCardsLabel.move({300, 10});

    centerCards.setParent(this);
    centerCards.showCards(gc.nest, DRAW_POSITION_CENTER, SIZE_SMALL);

    bottomCardsPreviewLabel.setParent(this);
    bottomCardsPreviewLabel.setText("New hand (click to discard)");
    bottomCardsPreviewLabel.setFont(QFont("Times", 12));
    bottomCardsPreviewLabel.move({300, 235});

    bottomCardsPreview.setParent(this);
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr, DRAW_POSITION_CENTER_PREVIEW, SIZE_SMALL);

    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
    setMaximumSize(size());
    setFixedSize(maximumSize());
}

NestDialog::~NestDialog()
{
    delete ui;
}

void NestDialog::autoChooseMiddleButtonPressed()
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

    centerCards.showCards(gc.nest, DRAW_POSITION_CENTER, SIZE_SMALL);
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr, DRAW_POSITION_CENTER_PREVIEW, SIZE_SMALL);
}

void NestDialog::doneMiddleButtonPressed()
{
    accept();
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

    centerCards.showCards(gc.nest, DRAW_POSITION_CENTER, SIZE_SMALL);
    bottomCardsPreview.showCards(gc.playerArr[PLAYER_1].cardArr, DRAW_POSITION_CENTER_PREVIEW, SIZE_SMALL);
}
