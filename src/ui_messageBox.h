/********************************************************************************
** Form generated from reading UI file 'messageBox.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEBOX_H
#define UI_MESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include "common.h"

QT_BEGIN_NAMESPACE

class Ui_MessageBox
{
public:
    ScaledQPushButton *okButton;
    ScaledQLabel *msgLabel;

    void setupUi(QDialog *MessageBox)
    {
        if (MessageBox->objectName().isEmpty())
            MessageBox->setObjectName(QStringLiteral("MessageBox"));
        MessageBox->setEnabled(true);
        MessageBox->resize(250, 250);
        okButton = new ScaledQPushButton(MessageBox);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(30, 210, 101, 28));
        QFont font;
        font.setPointSize(10);
        okButton->setFont(font);
        msgLabel = new ScaledQLabel(MessageBox);
        msgLabel->setObjectName(QStringLiteral("msgLabel"));
        msgLabel->setGeometry(QRect(44, 25, 401, 121));
        msgLabel->setFont(font);

        retranslateUi(MessageBox);

        QMetaObject::connectSlotsByName(MessageBox);
    } // setupUi

    void retranslateUi(QDialog *MessageBox)
    {
        MessageBox->setWindowTitle(QApplication::translate("MessageBox", "Message Box", 0));
        okButton->setText(QApplication::translate("MessageBox", "OK", 0));
        msgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MessageBox: public Ui_MessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEBOX_H
