#ifndef BIDDIALOG_H
#define BIDDIALOG_H

#include <QDialog>
#include <QMainWindow>

#include "common.h"
#include "ui_BidDialog.h"

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class BidDialog : public ScaledQDialog
{
    QMainWindow *mainWindow;

public:

    BidDialog(QMainWindow *pMainWindow, QWidget *parent = nullptr);
    virtual ~BidDialog();

    void resetLabelsAndComboBox();

    void onBidButtonPressed();
    void onPassButtonPressed();
    
    void setupComboBox(int minBid, int maxBid, int incr);

private:
    Ui::BidDialog ui;

    int getNumPassed();
    void showBidResultMsgBox();
};

#endif