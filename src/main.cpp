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

    SCALE_FACTOR = Utils::Ui::getScaleFactor(0.85F);
    
    MainWindow mainWindow;
    Utils::Ui::moveWindowToCenter(&mainWindow, 36);
    mainWindow.show();

    return a.exec();
}