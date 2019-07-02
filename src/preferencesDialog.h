#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "AppearancePage.h"
#include "GamePage.h"

class PreferencesDialog : public QDialog
{
    MainWindow *mainWindow; // non-owning

    // when using a layout, objects must be allocated on the heap
    QListWidget *contentsWidget;
    QListWidgetItem *appearanceButton;
    QListWidgetItem *gameButton;

    QStackedWidget *pagesWidget;
    AppearancePage *appearancePage;
    GamePage *gamePage;

    QHBoxLayout *horizontalLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonsLayout;

    QPushButton *closeButton;

    int *x;

public:
    PreferencesDialog(MainWindow *pMainWindow, QWidget *parent = nullptr);

    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void onCloseButton();
};

#endif