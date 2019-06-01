#include <vector>

#include "messageBox.h"

using namespace std;

MessageBox::MessageBox(QWidget *parent) : QDialogWithClickableCardArray(true, parent),
                                          messageBoxCards(DRAW_POSITION_MESSAGE_BOX, SIZE_SMALL, this)
{
    ui.setupUi(this);
    ui.msgLabel->setAlignment(Qt::AlignTop);

    QObject::connect(ui.okButton, &QPushButton::pressed, this, &MessageBox::okButtonPressed);

    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

void MessageBox::rescale()
{
    updateScaleFactor();
    setGeometry(geometry());

    for(auto label : vector<ScaledQLabel *>{ui.msgLabel})
        label->rescale();
    
    for(auto button : vector<ScaledQPushButton *>{ui.okButton})
        button->rescale();

    for(auto clickableCardArray : vector<ClickableCardArray *>{&messageBoxCards})
        clickableCardArray->rescale();
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
