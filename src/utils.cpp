#include <QApplication>
#include <QDesktopWidget>

#include "bidDialog.h"
#include "ui_BidDialog.h"
#include "clickableCard.h"
#include "handInfo.h"
#include "mainWidget.h"
#include "mainWindow.h"
#include "messageBox.h"
#include "ui_MessageBox.h"
#include "middleDialog.h"
#include "ui_MiddleDialog.h"
#include "roundInfo.h"
#include "roundSummaryDialog.h"
#include "utils.h"

namespace Utils
{
namespace Ui
{
float getScaleFactor(float desiredScreenRatio)
{
    float screenRatio = min(0.925F, desiredScreenRatio);

    QSize origSize = {1200, 850};
    QRect maxSize = QApplication::desktop()->screenGeometry(); // i.e. 1920x1080
    float factor = min((float)maxSize.width() / origSize.width(),
                       (float)maxSize.height() / origSize.height());

    return factor * screenRatio;
}

void moveWindowToCenter(QMainWindow *mainWindow, int taskBarHeight)
{
    auto screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - mainWindow->width()) / 2;
    int y = max(0, (screenGeometry.height() - mainWindow->height()) / 2 - taskBarHeight);
    mainWindow->move(QPoint(x, y));
}

void moveDialog(QDialog *dialog, QMainWindow *mainWindow, int position)
{
    auto mainWindowPos = mainWindow->pos();
    auto mainWindowSize = mainWindow->size();
    auto mainWindowCenter = QPoint(mainWindowPos.x() + mainWindowSize.width() / 2,
                                   mainWindowPos.y() + mainWindowSize.height() / 2);

    auto dialogSize = dialog->size();

    auto dialogPos = [&]() -> QPoint {
        auto centerPos = QPoint(mainWindowCenter.x() - dialogSize.width() / 2,
                                mainWindowCenter.y() - dialogSize.height() / 2);

        switch (position)
        {
        case DIALOG_POSITION_CENTER:
            return centerPos;

        case DIALOG_POSITION_MIDDLE_DLG:
            return QPoint(centerPos.x(), centerPos.y() - mainWindowSize.height() * 0.1F);

        case DIALOG_POSITION_NEST_DLG:
            return QPoint(centerPos.x(), centerPos.y() - mainWindowSize.height() * 0.1F);

        case DIALOG_POSITION_TRUMP_DLG:
            return QPoint(centerPos.x(), centerPos.y() - mainWindowSize.height() * 0.1F);

        case DIALOG_POSITION_PARTNER_DLG:
            return QPoint(centerPos.x(), centerPos.y() - mainWindowSize.height() * 0.1F);

        case DIALOG_POSITION_CARD_MESSAGE_BOX:
            return QPoint(centerPos.x() + mainWindowSize.width() * 0.35F, centerPos.y());

        default:
            return {0, 0};
        }
    }();

    dialog->move(QPoint({max(0, dialogPos.x()), max(0, dialogPos.y())}));
}

void setupMessageBox(MessageBox *msgBox, QString msg, QString title, QSize size)
{
    msgBox->setText(msg);
    msgBox->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    msgBox->resize(size);
    msgBox->setWindowTitle(title);
}
} // namespace Ui

namespace Stat
{
double phi(double x)
{
    // constants
    double a1 = 0.254829592;
    double a2 = -0.284496736;
    double a3 = 1.421413741;
    double a4 = -1.453152027;
    double a5 = 1.061405429;
    double p = 0.3275911;

    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x) / sqrt(2.0);

    // A&S formula 7.1.26
    double t = 1.0 / (1.0 + p * x);
    double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

    return 0.5 * (1.0 + sign * y);
}
} // namespace Stat

} // namespace Utils