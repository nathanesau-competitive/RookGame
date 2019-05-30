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
extern float scalefactor;
extern QPixmapCache pixmapcache;

class ScaledQLabel : public QLabel
{
    float prevScaleFactor;
    float scaleFactor;

public:
    ScaledQLabel(QWidget *parent = nullptr);

    void rescale();

    // override functions related to size or position
    void setFont(const QFont &font);
    void setGeometry(const QRect &rect);
    void resize(int w, int h);
    void move(const QPoint &pos);
};

class ScaledQPushButton : public QPushButton
{
    float prevScaleFactor;
    float scaleFactor;

public:
    ScaledQPushButton(QWidget *parent = nullptr);

    void rescale();

    // override functions related to size or position
    virtual void setFont(const QFont &font);
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void move(const QPoint &pos);
};

class ScaledQComboBox : public QComboBox
{
    float prevScaleFactor;
    float scaleFactor;

public:
    ScaledQComboBox(QWidget *parent);

    void rescale();

    // override functions related to size or position
    virtual void setFont(const QFont &font);
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void move(const QPoint &pos);
};

class ScaledQCheckBox : public QCheckBox
{
    float prevScaleFactor;
    float scaleFactor;

public:
    ScaledQCheckBox(QWidget *parent = nullptr);

    void rescale();

    // override functions related to size or position
    virtual void setFont(const QFont &font);
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void move(const QPoint &pos);
};

class ScaledQDialog : public QDialog
{
    bool fixedSize;
    float prevScaleFactor;
    float scaleFactor;

public:
    ScaledQDialog(bool pFixedSize, QWidget *parent = nullptr);

    void rescale();

    // override functions related to size or position
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void resize(const QSize &pSize);
    virtual void move(const QPoint &pos);
};

class ScaledQMainWindow : public QMainWindow
{
    float prevScaleFactor;
    float scaleFactor;

public:
    ScaledQMainWindow(QWidget *parent = nullptr);

    void rescale();

    // override functions related to size or position
    virtual void setGeometry(const QRect &rect);
    virtual void resize(int w, int h);
    virtual void resize(const QSize &pSize);
    virtual void move(const QPoint &pos);
};

#endif