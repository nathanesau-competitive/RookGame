#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>

#include "gameController.h"
#include "cpuPlayer.h"
#include "mainWindow.h"

#include <memory>

// globals
CpuPlayer cpu;
GameController gc;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;

    auto screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - mainWindow.width()) / 2;
    int y = (screenGeometry.height() - mainWindow.height()) / 2 - 50;
    mainWindow.move(x, y);

    mainWindow.show();

    return a.exec();
}