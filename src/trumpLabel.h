#ifndef TRUMPLABEL_H
#define TRUMPLABEL_H

#include <QLabel>
#include <QWidget>

class TrumpLabel : public QLabel
{
    Q_OBJECT // mousePressEvent

public:

    TrumpLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif