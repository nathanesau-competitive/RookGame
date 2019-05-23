#include <QPushButton>
#include <QObject>
#include <QMessageBox>
#include <string>

#include "gameController.h"
#include "mainWindow.h"
#include "middleDialog.h"
#include "nestDialog.h"
#include "partnerDialog.h"
#include "trumpDialog.h"
#include "utils.h"

using namespace std;

MiddleDialog::MiddleDialog(int &pTrumpSuitSelected, Card &pPartnerCardSelected,
                           MainWidget *pMainWidget, QMainWindow *pMainWindow, QWidget *parent) : trumpSuitSelected(pTrumpSuitSelected),
                                                                                                 partnerCardSelected(pPartnerCardSelected),
                                                                                                 mainWidget(pMainWidget),
                                                                                                 mainWindow(pMainWindow),
                                                                                                 QDialogWithClickableCardArray(parent),
                                                                                                 topRightCards(DRAW_POSITION_MIDDLE_DLG_NEST, SIZE_TINY, this),
                                                                                                 bottomRightCards(DRAW_POSITION_MIDDLE_DLG_PARTNER, SIZE_TINY, this)
{
    ui.setupUi(this);

    topRightCards.showCards(gc.nest);
    bottomRightCards.showCards({Card(SUIT_UNDEFINED, VALUE_UNDEFINED)});

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

    resize(724, 435);
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
    Utils::Ui::moveDialog(&nestDlg, mainWindow, DIALOG_POSITION_NEST_DLG);

    if (!nestDlg.exec())
    {
        qFatal("Problem executing nest dialog");
        return;
    }

    topRightCards.showCards(gc.nest);
    mainWidget->showBottomCards(gc.playerArr[PLAYER_1].cardArr);
}

void MiddleDialog::autoSelectNestButtonPressed()
{
    NestDialog::autoChooseNest();

    topRightCards.showCards(gc.nest);
    mainWidget->showBottomCards(gc.playerArr[PLAYER_1].cardArr);
}

void MiddleDialog::selectTrumpButtonPressed()
{
    TrumpDialog trumpDlg(trumpSuitSelected);
    Utils::Ui::moveDialog(&trumpDlg, mainWindow, DIALOG_POSITION_TRUMP_DLG);

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
    Utils::Ui::moveDialog(&partnerDlg, mainWindow, DIALOG_POSITION_PARTNER_DLG);

    if (!partnerDlg.exec())
    {
        qFatal("Problem executing partner dialog");
        return;
    }

    bottomRightCards.showCards({partnerCardSelected});
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
        bottomRightCards.showCards({partnerCardSelected});
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
