#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>

#include "clickableCard.h"
#include "common.h"

class MessageBox : public QDialogWithClickableCardArray
{
    ScaledQLabel *msgLabel;
    ScaledQPushButton *okButton;
    ClickableCardArray *messageBoxCards;

public:
    MessageBox(QWidget *parent = nullptr);
    virtual void rescale();

    void reject() {}

    void setText(const QString &text);
    void showCards(const CardVector &cardArr);

protected:
    void okButtonPressed();

    void onCardClicked(ClickableCard *clickableCard)
    {
        // do nothing
    }

    void onCardHoverEnter(ClickableCard *clickableCard)
    {
        // do nothing
    }

    void onCardHoverLeave(ClickableCard *clickableCard)
    {
        // do nothing
    }
};

#endif