#include <QPushButton>
#include <QObject>
#include <QMessageBox>
#include <string>

#include "trumpDialog.h"
#include "gameController.h"
#include "mainWindow.h"
#include "ui_TrumpDialog.h"

TrumpDialog::TrumpDialog(int &pTrumpSuitSelected, Card &pPartnerCardSelected, QWidget *parent) : trumpSuitSelected(pTrumpSuitSelected),
                                                                                                 partnerCardSelected(pPartnerCardSelected),
                                                                                                 QDialogWithClickableCardArray(parent),
                                                                                                 ui(new Ui::TrumpDialog)
{
    ui->setupUi(this);

    bottomRightCards.setParent(this);
    bottomRightCards.showCards({Card(SUIT_UNDEFINED, VALUE_UNDEFINED)}, DRAW_POSITION_TRUMP_DLG, SIZE_SMALL);

    QObject::connect(ui->selectTrumpButton, &QPushButton::pressed,
                     this, &TrumpDialog::selectSuitButtonPressed);

    QObject::connect(ui->selectCardButton, &QPushButton::pressed,
                     this, &TrumpDialog::selectCardButtonPressed);

    QObject::connect(ui->okButton, &QPushButton::pressed,
                     this, &TrumpDialog::okButtonPressed);

    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

TrumpDialog::~TrumpDialog()
{
    delete ui;
}

void TrumpDialog::onCardClicked(ClickableCard *clickableCard)
{
    // do nothing
}

void TrumpDialog::selectSuitButtonPressed()
{
    TrumpSuitSubDialog subDlg(trumpSuitSelected);
    moveDialogToCenter(&subDlg);
    auto subDlgFinished = subDlg.exec();

    auto setupTrumpLabel = [](QLabel *trumpLabel, int suit) {
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
    };

    if (subDlgFinished)
    {
        setupTrumpLabel(ui->selectTrumpLabel, trumpSuitSelected);
    }
}

void TrumpDialog::selectCardButtonPressed()
{
    TrumpPartnerSubDialog subDlg(partnerCardSelected);
    moveDialogToCenter(&subDlg, -100);
    auto subDlgFinished = subDlg.exec();

    if (subDlgFinished)
    {
        bottomRightCards.showCards({partnerCardSelected}, DRAW_POSITION_TRUMP_DLG, SIZE_SMALL);
    }
}

void TrumpDialog::okButtonPressed()
{
    accept();
}

TrumpSuitSubDialog::TrumpSuitSubDialog(int &pSuitSelected, QWidget *parent) : suitSelected(pSuitSelected), QDialog(parent)
{
    auto setupTrumpLabel = [this](TrumpLabel &label, QString text, QString style, QPoint pos) {
        label.setFont(QFont("Times", 12));
        label.setText(text);
        label.setStyleSheet(style);
        label.setParent(this);
        label.move(pos);
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

TrumpSuitSubDialog::~TrumpSuitSubDialog()
{
    // todo
}

void TrumpSuitSubDialog::onTrumpLabelClicked(TrumpLabel *label)
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

TrumpPartnerSubDialog::TrumpPartnerSubDialog(Card &pCardSelected, QWidget *parent) : cardSelected(pCardSelected),
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

    vector<Card> cardArr;
    vector<Card> row1Arr;
    vector<Card> row2Arr;
    vector<Card> row3Arr;
    vector<vector<Card> *> rowArrays = {&row1Arr, &row2Arr, &row3Arr};

    auto fillCardArray = [](vector<Card> &outCardArr, const vector<Card> &inCardArr) {
        for (auto card : inCardArr)
        {
            outCardArr.push_back(card);
        }
    };

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

    fillCardArray(cardArr, gc.playerArr[PLAYER_2].cardArr);
    fillCardArray(cardArr, gc.playerArr[PLAYER_3].cardArr);
    fillCardArray(cardArr, gc.playerArr[PLAYER_4].cardArr);
    fillCardArray(cardArr, gc.nest);

    sortCardArray(cardArr);
    splitCardArray(rowArrays, cardArr);

    blackCards.showCards(row1Arr, DRAW_POSITION_PARTNER_DLG_ROW1, SIZE_SMALL);
    greenCards.showCards(row2Arr, DRAW_POSITION_PARTNER_DLG_ROW2, SIZE_SMALL);
    redCards.showCards(row3Arr, DRAW_POSITION_PARTNER_DLG_ROW3, SIZE_SMALL);
}

TrumpPartnerSubDialog::~TrumpPartnerSubDialog()
{
    // todo
}

void TrumpPartnerSubDialog::onCardClicked(ClickableCard *clickableCard)
{
    cardSelected.suit = clickableCard->data.suit;
    cardSelected.value = clickableCard->data.value;

    accept();
}