#include <QPushButton>
#include <QObject>
#include <QMessageBox>
#include <string>

#include "trumpDialog.h"
#include "gameController.h"
#include "mainWindow.h"
#include "ui_TrumpDialog.h"

TrumpDialog::TrumpDialog(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::TrumpDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->selectTrumpButton, &QPushButton::pressed,
                     this, &TrumpDialog::selectSuitButtonPressed);

    QObject::connect(ui->selectCardButton, &QPushButton::pressed,
                     this, &TrumpDialog::selectCardButtonPressed);

    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

TrumpDialog::~TrumpDialog()
{
    delete ui;
}

void TrumpDialog::selectSuitButtonPressed()
{
    TrumpSuitSubDialog subDlg;
    moveDialogToCenter(&subDlg);
    auto subDlgFinished = subDlg.exec();

    if (subDlgFinished)
    {
        // todo
    }
}

void TrumpDialog::selectCardButtonPressed()
{
    TrumpPartnerSubDialog subDlg;
    moveDialogToCenter(&subDlg);
    auto subDlgFinished = subDlg.exec();

    if (subDlgFinished)
    {
        // todo
    }
}

TrumpSuitSubDialog::TrumpSuitSubDialog(QWidget *parent) : QDialog(parent)
{
    auto setupTrumpLabel = [this](TrumpLabel &label, QString text, QString style, QPoint pos) {
        label.setFont(QFont("Times", 12));
        label.setText(text);
        label.setStyleSheet(style);
        label.setParent(this);
        label.move(pos);
    };

    setupTrumpLabel(redLabel, "Red", "background-color: red", QPoint(25,25));
    setupTrumpLabel(blackLabel, "Black", "background-color: black; color: white", QPoint(25, 125));
    setupTrumpLabel(greenLabel, "Green", "background-color: green", QPoint(25, 225));
    setupTrumpLabel(yellowLabel, "Yellow", "background-color: yellow", QPoint(25, 325));

    setGeometry(0, 0, 600, 450);
    setMaximumSize(QSize(600, 450));
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
    int x = 5; // todo8

    accept();
}

TrumpPartnerSubDialog::TrumpPartnerSubDialog(QWidget *parent) : QDialog(parent)
{
    blackCards.setParent(this);
    greenCards.setParent(this);
    redCards.setParent(this);
    yellowCards.setParent(this);
    specialCards.setParent(this);

    setWindowTitle("Click partner card...");
    setWindowIcon(QIcon(":rookicon.gif"));
    setGeometry(0, 0, 800, 650);
    setMaximumSize(QSize(800, 650));
    setFixedSize(maximumSize());

    vector<Card> blackCardArr;
    vector<Card> greenCardArr;
    vector<Card> redCardArr;
    vector<Card> yellowCardArr;
    vector<Card> specialCardArr;

    auto fillColorCardArrays = [&blackCardArr,
                                &greenCardArr,
                                &redCardArr,
                                &yellowCardArr,
                                &specialCardArr](vector<Card> &cardArr) {
        for (auto card : cardArr)
        {
            if (card.suit == SUIT_BLACK)
                blackCardArr.push_back(card);
            else if (card.suit == SUIT_GREEN)
                greenCardArr.push_back(card);
            else if (card.suit == SUIT_RED)
                redCardArr.push_back(card);
            else if (card.suit == SUIT_YELLOW)
                yellowCardArr.push_back(card);
            else if (card.suit == SUIT_SPECIAL)
                specialCardArr.push_back(card);
        }
    };

    fillColorCardArrays(gc.playerArr[PLAYER_2].cardArr);
    fillColorCardArrays(gc.playerArr[PLAYER_3].cardArr);
    fillColorCardArrays(gc.playerArr[PLAYER_4].cardArr);
    fillColorCardArrays(gc.nest);

    blackCards.showCards(blackCardArr, DRAW_POSITION_PARTNER_DLG_ROW1, SIZE_SMALL);
    greenCards.showCards(greenCardArr, DRAW_POSITION_PARTNER_DLG_ROW2, SIZE_SMALL);
    redCards.showCards(redCardArr, DRAW_POSITION_PARTNER_DLG_ROW3, SIZE_SMALL);
    yellowCards.showCards(yellowCardArr, DRAW_POSITION_PARTNER_DLG_ROW4, SIZE_SMALL);
    specialCards.showCards(specialCardArr, DRAW_POSITION_PARTNER_DLG_ROW5, SIZE_SMALL);
}

TrumpPartnerSubDialog::~TrumpPartnerSubDialog()
{
    // todo
}
