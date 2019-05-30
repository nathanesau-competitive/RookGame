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

    Utils::Db::readPreferences();
    
    MainWindow mainWindow;
    Utils::Ui::moveWindowToCenter(&mainWindow, 36);
    mainWindow.show();

    return a.exec();
}