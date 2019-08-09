#include <vector>

#include "messageBox.h"

using namespace std;

MessageBox::MessageBox(QWidget *parent) : QDialogWithClickableCardArray(true, parent)
{
    msgLabel = new ScaledQLabel(this);
    msgLabel->setAlignment(Qt::AlignTop);
    msgLabel->setGeometry(QRect(20, 20, 400, 200));
    msgLabel->setFont(QFont("Times", 10));

    okButton = new ScaledQPushButton(this);
    okButton->setGeometry(QRect(30, 210, 101, 28));
    okButton->setFont(QFont("Times", 10));
    okButton->setText("OK");

    QObject::connect(okButton, &QPushButton::pressed, this, &MessageBox::okButtonPressed);

    messageBoxCards = new ClickableCardArray(DRAW_POSITION_MESSAGE_BOX, SIZE_SMALL, this);
    messageBoxCards->hide();

    resize({400, 250});
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
    setWindowOpacity(1.0);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

void MessageBox::rescale()
{
    updateScaleFactor();
    setGeometry(geometry());

    for(auto label : vector<ScaledQLabel *>{msgLabel})
        label->rescale();
    
    for(auto button : vector<ScaledQPushButton *>{okButton})
        button->rescale();

    for(auto clickableCardArray : vector<ClickableCardArray *>{messageBoxCards})
        clickableCardArray->rescale();
}

void MessageBox::setText(const QString &text)
{
    msgLabel->setText(text);
}

void MessageBox::showCards(const CardVector &cardArr)
{
    messageBoxCards->showCards(cardArr);
}

void MessageBox::okButtonPressed()
{
    QDialog::accept();
}
