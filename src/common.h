#ifndef COMMON_H
#define COMMON_H

#include <QComboBox>
#include <QDialog>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMetaObject>
#include <QObject>
#include <QPushButton>
#include <QSize>
#include <QToolTip>
#include <QTransform>
#include <QVariant>
#include <QWidget>

// global declarations
extern float SCALE_FACTOR;

class ScaledQLabel : public QLabel
{
public:
    ScaledQLabel(QWidget *parent = nullptr);

    // override functions related to size or position
    void setFont(const QFont &font);
    void setGeometry(const QRect &rect);
    void resize(int w, int h);
    void move(const QPoint &pos);
    void setPixmap(const QPixmap &pixmap, QSize size, QTransform transform);
};

class ScaledQPushButton : public QPushButton
{
public:
    ScaledQPushButton(QWidget *parent = nullptr);

    // override functions related to size or position
    virtual void setFont(const QFont &font);
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void move(const QPoint &pos);
};

class ScaledQComboBox : public QComboBox
{
public:

    // override functions related to size or position
    ScaledQComboBox(QWidget *parent);
    virtual void setFont(const QFont &font);
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void move(const QPoint &pos);
};

class ScaledQDialog : public QDialog
{
public:

    // override functions related to size or position
    ScaledQDialog(QWidget *parent = nullptr);
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void resize(const QSize &pSize);
    virtual void move(const QPoint &pos);
};

class ScaledQMainWindow : public QMainWindow
{
public:
    ScaledQMainWindow(QWidget *parent = nullptr);

    // override functions related to size or position
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void resize(const QSize &pSize);
    virtual void move(const QPoint &pos);
};

#endif