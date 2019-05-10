#ifndef TRUMPDIALOG_H
#define TRUMPDIALOG_H

#include <QDialog>
#include <QLabel>

#include "trumpLabel.h"
#include "mainWindow.h"

namespace Ui
{
class TrumpDialog;
}

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class TrumpDialog : public QDialog
{
public:
    TrumpDialog(QWidget *parent = nullptr);
    virtual ~TrumpDialog();

private:
    Ui::TrumpDialog *ui;

    void selectSuitButtonPressed();
    void selectCardButtonPressed();
};

// for selecting a trump suit
class TrumpSuitSubDialog : public QDialog
{
    TrumpLabel blackLabel;
    TrumpLabel greenLabel;
    TrumpLabel redLabel;
    TrumpLabel yellowLabel;

public:
    TrumpSuitSubDialog(QWidget *parent = nullptr);
    virtual ~TrumpSuitSubDialog();

    void onTrumpLabelClicked(TrumpLabel *label);
};

// for selecting a partner card from available cards
class TrumpPartnerSubDialog : public QDialog
{
    ClickableCardArray blackCards;
    ClickableCardArray greenCards;
    ClickableCardArray redCards;
    ClickableCardArray yellowCards;
    ClickableCardArray specialCards;

public:
    TrumpPartnerSubDialog(QWidget *parent = nullptr);
    virtual ~TrumpPartnerSubDialog();
};

#endif