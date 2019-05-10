#include "trumpLabel.h"
#include "mainWindow.h"

TrumpLabel::TrumpLabel(QWidget *parent) : QLabel(parent)
{
}

void TrumpLabel::mousePressEvent(QMouseEvent *event)
{
    TrumpSuitSubDialog *parentDialog = dynamic_cast<TrumpSuitSubDialog *>(parentWidget ());

    parentDialog->onTrumpLabelClicked(this);
}