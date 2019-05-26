#ifndef COMMON_H
#define COMMON_H

#include <map>
#include <memory>
#include <QCheckBox>
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
#include <string>
#include <vector>

using namespace std;

// forward declarations
struct Card;
struct CardPixmapKey;
struct CompareCardPixmapKey;

// typedef declarations
typedef map<CardPixmapKey, unique_ptr<QPixmap>, CompareCardPixmapKey> QPixmapCache;

// global declarations
extern float SCALE_FACTOR;
extern QPixmapCache pixmapCache;

class ScaledQLabel : public QLabel
{
public:
    ScaledQLabel(QWidget *parent = nullptr);

    // override functions related to size or position
    void setFont(const QFont &font);
    void setGeometry(const QRect &rect);
    void resize(int w, int h);
    void move(const QPoint &pos);
    void setPixmap(const Card &data, QSize size, QTransform transform);
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
    ScaledQComboBox(QWidget *parent);

    // override functions related to size or position
    virtual void setFont(const QFont &font);
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void move(const QPoint &pos);
};

class ScaledQCheckBox : public QCheckBox
{
public:
    ScaledQCheckBox(QWidget *parent = nullptr);

    // override functions related to size or position
    virtual void setFont(const QFont &font);
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void move(const QPoint &pos);
};

class ScaledQDialog : public QDialog
{
public:
    ScaledQDialog(QWidget *parent = nullptr);

    // override functions related to size or position
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