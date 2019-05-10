#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QString>

namespace Ui
{
class MessageBox;
}

class MessageBox : public QDialog
{
public:
    MessageBox(QWidget *parent = nullptr);

    void setText(const QString &text);

private:
    Ui::MessageBox *ui;

    void okButtonPressed();
};

#endif