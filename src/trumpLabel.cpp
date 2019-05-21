#include "mainWindow.h"
#include "middleDialog.h"
#include "trumpLabel.h"

TrumpLabel::TrumpLabel(QWidget *parent) : QLabel(parent)
{
}

void TrumpLabel::mousePressEvent(QMouseEvent *event)
{
    TrumpDialog *parentDialog = dynamic_cast<TrumpDialog *>(parentWidget ());

    parentDialog->onTrumpLabelClicked(this);
}