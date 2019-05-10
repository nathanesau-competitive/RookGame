#include "nestDialog.h"
#include "gameController.h"
#include "mainWindow.h"
#include "ui_NestDialog.h"

NestDialog::NestDialog(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::NestDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->autoChooseMiddleButton, &QPushButton::pressed,
                     this, &NestDialog::autoChooseMiddleButtonPressed);

    QObject::connect(ui->doneMiddleButton, &QPushButton::pressed,
                     this, &NestDialog::doneMiddleButtonPressed);

    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
    
    centerCards.setParent(this);
    centerCards.showCards(gc.nest, DRAW_POSITION_CENTER, SIZE_NORMAL);
}

NestDialog::~NestDialog()
{
    delete ui;
}

/*
void MainWindow::onAutoChooseMiddleButtonPressed()
{
    for (auto card : gc.nest)
    {
        gc.playerArr[PLAYER_1].cardArr.push_back(card);
    }

    gc.nest.clear();

    sortCardArray(gc.playerArr[PLAYER_1].cardArr);

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

    auto suitInfoArr = getSuitInfoArr(gc.playerArr[PLAYER_1].cardArr);

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

    centerCards.showCards(gc.nest, DRAW_POSITION_CENTER);
    bottomCards.showCards(gc.playerArr[PLAYER_1].cardArr, DRAW_POSITION_BOTTOM);
}
*/


void NestDialog::autoChooseMiddleButtonPressed()
{
    for (auto card : gc.nest)
    {
        gc.playerArr[PLAYER_1].cardArr.push_back(card);
    }

    gc.nest.clear();

    sortCardArray(gc.playerArr[PLAYER_1].cardArr);

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

    auto suitInfoArr = getSuitInfoArr(gc.playerArr[PLAYER_1].cardArr);

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

    centerCards.showCards(gc.nest, DRAW_POSITION_CENTER);
    gui.mw->drawBottomCards(gc.playerArr[PLAYER_1].cardArr);
}

void NestDialog::doneMiddleButtonPressed()
{
    accept();
}

void NestDialog::onCardClicked(ClickableCard *clickableCard)
{
    /*centerCards.hideCards();
    autoChooseMiddleButton.hide();
    doneMiddleButton.hide();

    TrumpDialog trumpDlg(&widget);
    trumpDlg.move(QPoint(300, 200));
    auto trumpDlgFinished = trumpDlg.exec();
    trumpDlg.deleteLater();

    if (trumpDlgFinished)
    {
        showMessageBox("Game starting...", "Start Game", &widget);
        gc.startGame();
        int x = 5;
    }*/

    centerCards.showCards(gc.nest, DRAW_POSITION_CENTER);

    gui.mw->drawBottomCards(gc.playerArr[PLAYER_1].cardArr);
}
