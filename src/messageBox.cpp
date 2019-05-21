#include "messageBox.h"
#include "ui_MessageBox.h"

MessageBox::MessageBox(QWidget *parent) : QDialogWithClickableCardArray(parent),
                                          ui(new Ui::MessageBox)
{
    ui->setupUi(this);
    ui->msgLabel->setAlignment(Qt::AlignTop);

    messageBoxCards.setParent(this);

    QObject::connect(ui->okButton, &QPushButton::pressed, this, &MessageBox::okButtonPressed);

    setWindowIcon(QIcon(":rookicon.gif"));
}

void MessageBox::setText(const QString &text)
{
    ui->msgLabel->setText(text);
}

void MessageBox::showCards(const vector<Card> &cardArr)
{
    messageBoxCards.showCards(cardArr, DRAW_POSITION_MESSAGE_BOX, SIZE_SMALL);
}

void MessageBox::okButtonPressed()
{
    accept();
}
