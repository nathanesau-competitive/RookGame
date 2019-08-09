#include <QApplication>
#include <QDesktopWidget>
#include <QSettings>
#include <QScreen>

#include "bidDialog.h"
#include "ui_BidDialog.h"
#include "clickableCard.h"
#include "handInfo.h"
#include "mainWidget.h"
#include "mainWindow.h"
#include "messageBox.h"
#include "middleDialog.h"
#include "ui_MiddleDialog.h"
#include "roundInfo.h"
#include "roundSummaryDialog.h"
#include "utils.h"

namespace Utils
{
namespace Ui
{
QRect getScreenGeometry()
{
    QRect geometry = QApplication::desktop()->screenGeometry();
    geometry.setWidth(Utils::Db::readScreenWidthFromDb());
    geometry.setHeight(Utils::Db::readScreenHeightFromDb());

    return geometry;
}

float getBestScaleFactor()
{
    QSize origSize = {1200, 850};

    QRect maxSizeRect = Utils::Ui::getScreenGeometry();
    QSize maxSize = {maxSizeRect.width(), maxSizeRect.height()};

    float factor = min((float)maxSize.width() / origSize.width(),
                       (float)maxSize.height() / origSize.height());

    // DO NOT fill more than 90% of screen
    float bestScreenRatio = 0.9F;
    factor = factor * bestScreenRatio;
    factor = round(factor * 10) / 10.0F;

    return factor;
}

QSize getResolution(float scaleFactor)
{
    int width = 1200 * scaleFactor;
    int height = 850 * scaleFactor;

    return {width, height};
}

void moveWindowToCenter(QWidget *widget, int taskBarHeight /*=0*/)
{
    auto screenGeometry = Utils::Ui::getScreenGeometry();
    int x = (screenGeometry.width() - widget->width()) / 2;
    int y = max(0, (screenGeometry.height() - widget->height()) / 2 - taskBarHeight);
    widget->move(QPoint(x, y));
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
    //msgBox->resize(size);
    msgBox->setWindowTitle(title);
}
} // namespace Ui

namespace Db
{
float readScaleFactorFromDb()
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    float scaleFactor = settings.value("scalefactor", Utils::Ui::getBestScaleFactor()).toFloat();
    settings.endGroup();

    return scaleFactor;
}

map<int, string> readPlayerNamesFromDb()
{
    map<int, string> playerNames;

    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");

    auto readPlayerName = [&](int playerNum, QString key, QString defaultValue)
    {
        QString name = settings.value(key, defaultValue).toString();
        playerNames[playerNum] = name.toStdString();
    };

    readPlayerName(PLAYER_1, "Player1Name", "Player 1");
    readPlayerName(PLAYER_2, "Player2Name", "Player 2");
    readPlayerName(PLAYER_3, "Player3Name", "Player 3");
    readPlayerName(PLAYER_4, "Player4Name", "Player 4");

    settings.endGroup();

    return playerNames;
}

bool readShowNameTagsFromDb()
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    bool showNameTags = settings.value("showNameTags", true).toBool();
    settings.endGroup();

    return showNameTags;
}

bool readShowPartnerToolTipFromDb()
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    bool showPartnerToolTip = settings.value("showPartnerToolTip", false).toBool();
    settings.endGroup();

    return showPartnerToolTip;
}

int readScreenWidthFromDb()
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    int screenWidth = settings.value("screenWidth", QApplication::desktop()->screenGeometry().width()).toInt();
    settings.endGroup();

    return screenWidth;
}

int readScreenHeightFromDb()
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    int screenHeight = settings.value("screenHeight", QApplication::desktop()->screenGeometry().height()).toInt();
    settings.endGroup();

    return screenHeight;
}

void writeScaleFactorToDb(float scaleFactor)
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    settings.setValue("scalefactor", scaleFactor);
    settings.endGroup();
}

void writePlayerNamesToDb(map<int, string> playerNames)
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    settings.setValue("Player1Name", QString::fromStdString(playerNames[PLAYER_1]));
    settings.setValue("Player2Name", QString::fromStdString(playerNames[PLAYER_2]));
    settings.setValue("Player3Name", QString::fromStdString(playerNames[PLAYER_3]));
    settings.setValue("Player4Name", QString::fromStdString(playerNames[PLAYER_4]));
    settings.endGroup();
}

void writeShowNameTagsToDb(bool showNameTags)
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    settings.setValue("showNameTags", showNameTags);
    settings.endGroup();
}

void writeShowPartnerToolTipToDb(bool showPartnerToolTip)
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    settings.setValue("showPartnerToolTip", showPartnerToolTip);
    settings.endGroup();
}

void writeScreenWidthToDb(int screenWidth)
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    settings.setValue("screenWidth", screenWidth);
    settings.endGroup();
}

void writeScreenHeightToDb(int screenHeight)
{
    QSettings settings("OpenSourceSoftware", "Rook");
    settings.beginGroup("Appearance");
    settings.setValue("screenHeight", screenHeight);
    settings.endGroup();
}
} // namespace Db

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