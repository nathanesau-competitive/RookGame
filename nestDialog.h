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

class NestDialog : public QDialog
{
    ClickableCardArray centerCards;

public:
    NestDialog(QWidget *parent = nullptr);
    virtual ~NestDialog();

private:
    Ui::NestDialog *ui;
    
    void autoChooseMiddleButtonPressed();
    void doneMiddleButtonPressed();
    void onCardClicked(ClickableCard *clickableCard);
};

#endif