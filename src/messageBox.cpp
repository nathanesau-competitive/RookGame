#include "messageBox.h"

MessageBox::MessageBox(QWidget *parent) : QDialogWithClickableCardArray(true, parent),
                                          messageBoxCards(DRAW_POSITION_MESSAGE_BOX, SIZE_SMALL, this)
{
    ui.setupUi(this);
    ui.msgLabel->setAlignment(Qt::AlignTop);

    QObject::connect(ui.okButton, &QPushButton::pressed, this, &MessageBox::okButtonPressed);

    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

void MessageBox::setText(const QString &text)
{
    ui.msgLabel->setText(text);
}

void MessageBox::showCards(const CardVector &cardArr)
{
    messageBoxCards.showCards(cardArr);
}

void MessageBox::okButtonPressed()
{
    accept();
}
