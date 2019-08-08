#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>

#include "clickableCard.h"
#include "common.h"
#include "ui_MessageBox.h" // uic -o ui_messageBox.h messageBox.ui

class MessageBox : public QDialogWithClickableCardArray
{
public:
    MessageBox(QWidget *parent = nullptr);
    virtual void rescale();

    void setText(const QString &text);
    void showCards(const CardVector &cardArr);

protected:
    Ui::MessageBox ui;

    ClickableCardArray *messageBoxCards;

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