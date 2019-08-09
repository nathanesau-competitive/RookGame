#include <QApplication>
#include <QCoreApplication>

#include "gameController.h"
#include "cpuPlayer.h"
#include "mainWindow.h"
#include "utils.h"

// globals
float scalefactor;
CpuPlayer cpu;
GameController gc;
QPixmapCache pixmapcache;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    scalefactor = Utils::Db::readScaleFactorFromDb();
    
    MainWindow mainWindow;

    //#ifdef WIN32
    Utils::Ui::moveWindowToCenter(&mainWindow, 0);
    //#endif

    mainWindow.show();

    return a.exec();
}