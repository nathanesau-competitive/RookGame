#include <QApplication>
#include <QCoreApplication>

#include "gameController.h"
#include "cpuPlayer.h"
#include "mainWindow.h"

#include <memory>

// globals
CpuPlayer cpu;
GameController gc;
Interface gui;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mw;

    mw.show();
    gui.mw = &mw;

    return a.exec();
}