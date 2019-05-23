#include "messageBox.h"

MessageBox::MessageBox(QWidget *parent) : QDialogWithClickableCardArray(parent),
                                          messageBoxCards(DRAW_POSITION_MESSAGE_BOX, SIZE_SMALL, this)
{
    ui.setupUi(this);
    ui.msgLabel->setAlignment(Qt::AlignTop);

    QObject::connect(ui.okButton, &QPushButton::pressed, this, &MessageBox::okButtonPressed);

    setWindowIcon(QIcon(":rookicon.gif"));
}

void MessageBox::setText(const QString &text)
{
    ui.msgLabel->setText(text);
}

void MessageBox::showCards(const vector<Card> &cardArr)
{
    messageBoxCards.showCards(cardArr);
}

void MessageBox::okButtonPressed()
{
    accept();
}
