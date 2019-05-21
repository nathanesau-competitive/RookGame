#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <string>

#include "bidDialog.h"
#include "gameController.h"
#include "ui_BidDialog.h"
#include "utils.h"

using namespace std;

BidDialog::BidDialog(QMainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                  QDialog(parent),
                                                                  ui(new Ui::BidDialog)
{
    ui->setupUi(this);

    setupComboBox(40, 120, 5);

    ui->bidAmountLabel->adjustSize();
    ui->player1Label->adjustSize();
    ui->player2Label->adjustSize();
    ui->player3Label->adjustSize();
    ui->player4Label->adjustSize();

    QObject::connect(ui->bidButton, &QPushButton::pressed, this, &BidDialog::onBidButtonPressed);
    QObject::connect(ui->passButton, &QPushButton::pressed, this, &BidDialog::onPassButtonPressed);

    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

BidDialog::~BidDialog()
{
    delete ui;
}

void BidDialog::resetLabelsAndComboBox()
{
    ui->player1BidLabel->setText("");
    ui->player2BidLabel->setText("");
    ui->player3BidLabel->setText("");
    ui->player4BidLabel->setText("");
    setupComboBox(40, 120, 5);
}

void BidDialog::onBidButtonPressed()
{
    gc.bid(ui->bidAmountComboBox->currentText().toInt());

    auto showBid = [](QLabel *label, int bid) {
        QString bidText = (bid == 0) ? "Pass" : QString::number(bid);
        label->setText(bidText);
    };

    showBid(ui->player1BidLabel, gc.playerArr[PLAYER_1].bid);
    showBid(ui->player2BidLabel, gc.playerArr[PLAYER_2].bid);
    showBid(ui->player3BidLabel, gc.playerArr[PLAYER_3].bid);
    showBid(ui->player4BidLabel, gc.playerArr[PLAYER_4].bid);

    if (gc.bidPlayer != PLAYER_UNDEFINED) // bidding round over
    {
        accept(); // close bid dialog
        showBidResultMsgBox();
    }
    else
    {
        setupComboBox(gc.bidAmount + 5, 120, 5);
    }
}

void BidDialog::onPassButtonPressed()
{
    gc.pass();
    accept(); // close bid dialog
    showBidResultMsgBox();
}

void BidDialog::setupComboBox(int minBid, int maxBid, int incr)
{
    ui->bidAmountComboBox->clear();

    for (int bid = minBid; bid <= maxBid; bid += incr)
    {
        QString itemText = QString::number(bid);
        ui->bidAmountComboBox->addItem(itemText);
    }

    ui->bidAmountComboBox->showNormal();
}

int BidDialog::getNumPassed()
{
    int numPassed = 0;

    for (auto &player : gc.playerArr)
    {
        if (player.bid == 0)
        {
            numPassed++;
        }
    }

    return numPassed;
}

void BidDialog::showBidResultMsgBox()
{
    string bidResultMsg = Utils::Ui::getPlayerName(gc.bidPlayer) + " won the bid for " +
                          to_string(gc.bidAmount) + ". " + "Bid updated.";

    MessageBox msgBox;
    Utils::Ui::setupMessageBox(&msgBox, QString::fromStdString(bidResultMsg), "Bid Result");
    Utils::Ui::moveDialogToCenter(&msgBox, mainWindow);
    msgBox.exec();
}