#ifndef NESTDIALOG_H
#define NESTDIALOG_H

#include <QDialog>

#include "clickableCard.h"

namespace Ui
{
class NestDialog;
}

// forward declarations
class GameController;

// global declarations
extern GameController gc;

class NestDialog : public QDialogWithClickableCardArray
{
    ClickableCardArray centerCards;

public:
    NestDialog(QWidget *parent = nullptr);
    virtual ~NestDialog();

private:
    Ui::NestDialog *ui;
    
    virtual void onCardClicked(ClickableCard *clickableCard);

    void autoChooseMiddleButtonPressed();
    void doneMiddleButtonPressed();
};

#endif