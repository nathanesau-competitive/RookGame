#include <QApplication>
#include <QCoreApplication>

#include "gameController.h"
#include "cpuPlayer.h"
#include "mainWindow.h"
#include "utils.h"

// globals
float SCALE_FACTOR;
CpuPlayer cpu;
GameController gc;
QPixmapCache pixmapCache;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Utils::Db::readPreferences();

    if (SCALE_FACTOR == 0.0F)
    {
        SCALE_FACTOR = Utils::Ui::getBestScaleFactor();
    }
    
    MainWindow mainWindow;
    Utils::Ui::moveWindowToCenter(&mainWindow, 36);
    mainWindow.show();

    return a.exec();
}