#include "common.h"

ScaledQLabel::ScaledQLabel(QWidget *parent) : QLabel(parent)
{
}

void ScaledQLabel::setFont(const QFont &font)
{
    auto scaledFont = font;
    scaledFont.setPointSizeF(scaledFont.pointSizeF() * SCALE_FACTOR);

    QLabel::setFont(scaledFont);
}

void ScaledQLabel::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * SCALE_FACTOR, rect.y() * SCALE_FACTOR,
                            rect.width() * SCALE_FACTOR, rect.height() * SCALE_FACTOR);

    QLabel::setGeometry(scaledRect);
}

void ScaledQLabel::resize(int w, int h)
{
    QLabel::resize(w * SCALE_FACTOR, h * SCALE_FACTOR);
}

void ScaledQLabel::move(const QPoint &pos)
{
    QLabel::move(pos * SCALE_FACTOR);
}

void ScaledQLabel::setPixmap(const QPixmap &pixmap, QSize size, QTransform transform)
{
    QPixmap scaledPixmap = pixmap;  
    QLabel::setPixmap(scaledPixmap.scaled(size * SCALE_FACTOR, Qt::KeepAspectRatio, Qt::SmoothTransformation).transformed(transform));
}

ScaledQPushButton::ScaledQPushButton(QWidget *parent) : QPushButton(parent)
{
}

void ScaledQPushButton::setFont(const QFont &font)
{
    auto scaledFont = font;
    scaledFont.setPointSizeF(font.pointSizeF() * SCALE_FACTOR);

    QPushButton::setFont(scaledFont);
}

void ScaledQPushButton::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * SCALE_FACTOR, rect.y() * SCALE_FACTOR,
                            rect.width() * SCALE_FACTOR, rect.height() * SCALE_FACTOR);

    QPushButton::setGeometry(scaledRect);
}

void ScaledQPushButton::move(const QPoint &pos)
{
   QPushButton::move(pos * SCALE_FACTOR);
}

void ScaledQPushButton::resize(int w, int h)
{
    QPushButton::resize(w * SCALE_FACTOR, h * SCALE_FACTOR);
}

ScaledQComboBox::ScaledQComboBox(QWidget *parent) : QComboBox(parent)
{
}

void ScaledQComboBox::setFont(const QFont &font)
{
    auto scaledFont = font;
    scaledFont.setPointSizeF(font.pointSizeF() * SCALE_FACTOR);

    QComboBox::setFont(scaledFont);
}

void ScaledQComboBox::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * SCALE_FACTOR, rect.y() * SCALE_FACTOR,
                            rect.width() * SCALE_FACTOR, rect.height() * SCALE_FACTOR);

    QComboBox::setGeometry(scaledRect);
}

void ScaledQComboBox::resize(int w, int h)
{
    QComboBox::resize(w * SCALE_FACTOR, h * SCALE_FACTOR);
}

void ScaledQComboBox::move(const QPoint &pos)
{
    QComboBox::move(pos * SCALE_FACTOR);
}

ScaledQDialog::ScaledQDialog(QWidget *parent) : QDialog(parent)
{
}

void ScaledQDialog::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * SCALE_FACTOR, rect.y() * SCALE_FACTOR,
                            rect.width() * SCALE_FACTOR, rect.height() * SCALE_FACTOR);

    QDialog::setGeometry(scaledRect);
    QDialog::setMaximumSize(size());
    QDialog::setFixedSize(size());
}

void ScaledQDialog::resize(int w, int h)
{
    QDialog::resize(w * SCALE_FACTOR, h * SCALE_FACTOR);
    QDialog::setMaximumSize(size());
    QDialog::setFixedSize(size());
}

void ScaledQDialog::resize(const QSize &pSize)
{
    QDialog::resize(pSize * SCALE_FACTOR);
    QDialog::setMaximumSize(size());
    QDialog::setFixedSize(size());
}

void ScaledQDialog::move(const QPoint &pos)
{
    QDialog::move(pos * SCALE_FACTOR);
}

ScaledQMainWindow::ScaledQMainWindow(QWidget *parent) : QMainWindow(parent)
{
}

void ScaledQMainWindow::setGeometry(const QRect &rect)
{
    auto scaledRect = QRect(rect.x() * SCALE_FACTOR, rect.y() * SCALE_FACTOR,
                            rect.width() * SCALE_FACTOR, rect.height() * SCALE_FACTOR);

    QMainWindow::setGeometry(scaledRect);
    QMainWindow::setMaximumSize(size());
    QMainWindow::setFixedSize(size());
}

void ScaledQMainWindow::resize(int w, int h)
{
    QMainWindow::resize(w * SCALE_FACTOR, h * SCALE_FACTOR);
    QMainWindow::setMaximumSize(size());
    QMainWindow::setFixedSize(size());
}

void ScaledQMainWindow::resize(const QSize &pSize)
{
    QMainWindow::resize(pSize * SCALE_FACTOR);
    QMainWindow::setMaximumSize(size());
    QMainWindow::setFixedSize(size());
}

void ScaledQMainWindow::move(const QPoint &pos)
{
    QMainWindow::move(pos * SCALE_FACTOR);
}