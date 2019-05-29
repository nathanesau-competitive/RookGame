#include "card.h"
#include "common.h"

ScaledQLabel::ScaledQLabel(QWidget *parent) : QLabel(parent)
{
    scaleFactor = SCALE_FACTOR;
    prevScaleFactor = SCALE_FACTOR;
}

void ScaledQLabel::rescale()
{
    float newScaleFactor = SCALE_FACTOR;
    scaleFactor = newScaleFactor / prevScaleFactor;
    prevScaleFactor = newScaleFactor;

    setFont(font());
    setGeometry(geometry());
}

void ScaledQLabel::setFont(const QFont &font)
{
    auto scaledFont = font;
    scaledFont.setPointSizeF(scaledFont.pointSizeF() * scaleFactor);

    QLabel::setFont(scaledFont);
}

void ScaledQLabel::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * scaleFactor, rect.y() * scaleFactor,
                            rect.width() * scaleFactor, rect.height() * scaleFactor);

    QLabel::setGeometry(scaledRect);
}

void ScaledQLabel::resize(int w, int h)
{
    QLabel::resize(w * scaleFactor, h * scaleFactor);
}

void ScaledQLabel::move(const QPoint &pos)
{
    QLabel::move(pos * scaleFactor);
}

ScaledQPushButton::ScaledQPushButton(QWidget *parent) : QPushButton(parent)
{
    scaleFactor = SCALE_FACTOR;
    prevScaleFactor = SCALE_FACTOR;
}

void ScaledQPushButton::rescale()
{
    float newScaleFactor = SCALE_FACTOR;
    scaleFactor = newScaleFactor / prevScaleFactor;
    prevScaleFactor = newScaleFactor;

    setFont(font());
    setGeometry(geometry());
}

void ScaledQPushButton::setFont(const QFont &font)
{
    auto scaledFont = font;
    scaledFont.setPointSizeF(font.pointSizeF() * scaleFactor);

    QPushButton::setFont(scaledFont);
}

void ScaledQPushButton::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * scaleFactor, rect.y() * scaleFactor,
                            rect.width() * scaleFactor, rect.height() * scaleFactor);

    QPushButton::setGeometry(scaledRect);
}

void ScaledQPushButton::move(const QPoint &pos)
{
    QPushButton::move(pos * scaleFactor);
}

void ScaledQPushButton::resize(int w, int h)
{
    QPushButton::resize(w * scaleFactor, h * scaleFactor);
}

ScaledQComboBox::ScaledQComboBox(QWidget *parent) : QComboBox(parent)
{
    scaleFactor = SCALE_FACTOR;
    prevScaleFactor = SCALE_FACTOR;
}

void ScaledQComboBox::rescale()
{
    float newScaleFactor = SCALE_FACTOR;
    scaleFactor = newScaleFactor / prevScaleFactor;
    prevScaleFactor = newScaleFactor;

    setFont(font());
    setGeometry(geometry());
}

void ScaledQComboBox::setFont(const QFont &font)
{
    auto scaledFont = font;
    scaledFont.setPointSizeF(font.pointSizeF() * scaleFactor);

    QComboBox::setFont(scaledFont);
}

void ScaledQComboBox::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * scaleFactor, rect.y() * scaleFactor,
                            rect.width() * scaleFactor, rect.height() * scaleFactor);

    QComboBox::setGeometry(scaledRect);
}

void ScaledQComboBox::resize(int w, int h)
{
    QComboBox::resize(w * scaleFactor, h * scaleFactor);
}

void ScaledQComboBox::move(const QPoint &pos)
{
    QComboBox::move(pos * scaleFactor);
}

ScaledQCheckBox::ScaledQCheckBox(QWidget *parent) : QCheckBox(parent)
{
    scaleFactor = SCALE_FACTOR;
    prevScaleFactor = SCALE_FACTOR;
}

void ScaledQCheckBox::rescale()
{
    float newScaleFactor = SCALE_FACTOR;
    scaleFactor = newScaleFactor / prevScaleFactor;
    prevScaleFactor = newScaleFactor;

    setFont(font());
    setGeometry(geometry());
}

void ScaledQCheckBox::setFont(const QFont &font)
{
    auto scaledFont = font;
    scaledFont.setPointSizeF(font.pointSizeF() * scaleFactor);

    QCheckBox::setFont(scaledFont);
}

void ScaledQCheckBox::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * scaleFactor, rect.y() * scaleFactor,
                            rect.width() * scaleFactor, rect.height() * scaleFactor);

    QCheckBox::setGeometry(scaledRect);
}

void ScaledQCheckBox::resize(int w, int h)
{
    QCheckBox::resize(w * scaleFactor, h * scaleFactor);
}

void ScaledQCheckBox::move(const QPoint &pos)
{
    QCheckBox::move(pos * scaleFactor);
}

ScaledQDialog::ScaledQDialog(bool pFixedSize, QWidget *parent) : QDialog(parent)
{
    fixedSize = pFixedSize;
    scaleFactor = SCALE_FACTOR;
    prevScaleFactor = SCALE_FACTOR;
}

void ScaledQDialog::rescale()
{
    float newScaleFactor = SCALE_FACTOR;
    scaleFactor = newScaleFactor / prevScaleFactor;
    prevScaleFactor = newScaleFactor;

    setGeometry(geometry());
}

void ScaledQDialog::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * scaleFactor, rect.y() * scaleFactor,
                            rect.width() * scaleFactor, rect.height() * scaleFactor);

    if (fixedSize)
    {
        QDialog::setFixedSize(scaledRect.width(), scaledRect.height());
        QDialog::setMaximumSize(scaledRect.width(), scaledRect.height());
    }

    QDialog::setGeometry(scaledRect);
}

void ScaledQDialog::resize(int w, int h)
{
    if (fixedSize)
    {
        QDialog::setFixedSize(w * scaleFactor, h * scaleFactor);
        QDialog::setMaximumSize(w * scaleFactor, h * scaleFactor);
    }

    QDialog::resize(w * scaleFactor, h * scaleFactor);
}

void ScaledQDialog::resize(const QSize &pSize)
{
    if (fixedSize)
    {
        QDialog::setFixedSize(pSize * scaleFactor);
        QDialog::setMaximumSize(pSize * scaleFactor);
    }
    
    QDialog::resize(pSize * scaleFactor);
}

void ScaledQDialog::move(const QPoint &pos)
{
    QDialog::move(pos * scaleFactor);
}

ScaledQMainWindow::ScaledQMainWindow(QWidget *parent) : QMainWindow(parent)
{
    scaleFactor = SCALE_FACTOR;
    prevScaleFactor = SCALE_FACTOR;
}

void ScaledQMainWindow::rescale()
{
    float newScaleFactor = SCALE_FACTOR;
    scaleFactor = newScaleFactor / prevScaleFactor;
    prevScaleFactor = newScaleFactor;

    setGeometry(geometry());
}

void ScaledQMainWindow::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * scaleFactor, rect.y() * scaleFactor,
                            rect.width() * scaleFactor, rect.height() * scaleFactor);

    QMainWindow::setFixedSize(scaledRect.width(), scaledRect.height());
    QMainWindow::setMaximumSize(scaledRect.width(), scaledRect.height());
    QMainWindow::setGeometry(scaledRect);
}

void ScaledQMainWindow::resize(int w, int h)
{
    QMainWindow::setFixedSize(w * scaleFactor, h * scaleFactor);
    QMainWindow::setMaximumSize(w * scaleFactor, h * scaleFactor);
    QMainWindow::resize(w * scaleFactor, h * scaleFactor);
}

void ScaledQMainWindow::resize(const QSize &pSize)
{
    QMainWindow::setFixedSize(pSize * scaleFactor);
    QMainWindow::setMaximumSize(pSize * scaleFactor);
    QMainWindow::resize(pSize * scaleFactor);
}

void ScaledQMainWindow::move(const QPoint &pos)
{
    QMainWindow::move(pos * scaleFactor);
}