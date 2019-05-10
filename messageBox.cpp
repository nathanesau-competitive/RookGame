#include "messageBox.h"
#include "ui_MessageBox.h"

MessageBox::MessageBox(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::MessageBox)
{
    ui->setupUi(this);

    QObject::connect(ui->okButton, &QPushButton::pressed, this, &MessageBox::okButtonPressed);

    setWindowIcon(QIcon(":rookicon.gif"));
}

void MessageBox::setText(const QString &text)
{
    ui->msgLabel->setText(text);
}

void MessageBox::okButtonPressed()
{
    accept();
}