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
    // for detecting memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    QApplication a(argc, argv);

    scalefactor = Utils::Db::readScaleFactorFromDb();
    
    MainWindow mainWindow;
    Utils::Ui::moveWindowToCenter(&mainWindow, 36);
    mainWindow.show();

    return a.exec();
}