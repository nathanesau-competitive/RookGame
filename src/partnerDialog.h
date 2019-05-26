#ifndef PARTNERDIALOG_H
#define PARTNERDIALOG_H

#include "clickableCard.h"
#include "common.h"

// forward declarations
class GameController;
class PartnerDialog;

// global declarations
extern GameController gc;

class PartnerDialogLabel : public ScaledQLabel
{
    Q_OBJECT

public:
    PartnerDialogLabel(PartnerDialog *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
};

// for selecting a partner card from available cards
class PartnerDialog : public QDialogWithClickableCardArray
{
    Card &cardSelected;

    CardVector blackCards;
    CardVector greenCards;
    CardVector redCards;
    CardVector yellowCards;
    CardVector wildCards;

    PartnerDialogLabel blackLabel;
    PartnerDialogLabel greenLabel;
    PartnerDialogLabel redLabel;
    PartnerDialogLabel yellowLabel;
    PartnerDialogLabel wildLabel;

    ScaledQPushButton cancelButton;

    ClickableCardArray centerCards;

public:
    PartnerDialog(Card &pCardSelected, QWidget *parent = nullptr);
    virtual ~PartnerDialog();

    void onPartnerLabelClicked(PartnerDialogLabel *label);

    virtual void onCardClicked(ClickableCard *clickableCard);

    virtual void onCardHoverEnter(ClickableCard *clickableCard)
    {
        // do nothing
    }

    virtual void onCardHoverLeave(ClickableCard *clickableCard)
    {
        // do nothing
    }
};

#endif