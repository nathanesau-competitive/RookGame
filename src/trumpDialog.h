#ifndef TRUMPDIALOG_H
#define TRUMPDIALOG_H

#include <string>

#include "common.h"

using namespace std;

// forward declarations
class TrumpDialog;

class TrumpDialogLabel : public ScaledQLabel
{
    Q_OBJECT

public:

    TrumpDialogLabel(TrumpDialog *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
};

// for selecting a trump suit
class TrumpDialog : public ScaledQDialog
{
    int &suitSelected;

    TrumpDialogLabel blackLabel;
    TrumpDialogLabel greenLabel;
    TrumpDialogLabel redLabel;
    TrumpDialogLabel yellowLabel;

public:
    TrumpDialog(int &pSuitSelected, QWidget *parent = nullptr);

    virtual ~TrumpDialog();
    void onTrumpLabelClicked(TrumpDialogLabel *label);
};

#endif