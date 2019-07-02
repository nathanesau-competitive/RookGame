#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QCheckBox>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class GamePage : public QWidget
{
    // when using a layout, objects must be allocated on the heap
    QGroupBox updateGroup;
    QVBoxLayout updateLayout;
    QCheckBox systemCheckBox;
    QCheckBox appsCheckBox;
    QCheckBox docsCheckBox;
    
    QGroupBox packageGroup;
    QVBoxLayout packageLayout;
    QListWidget packageList;
    QListWidgetItem qtItem;
    QListWidgetItem qsaItem;
    QListWidgetItem teamBuilderItem;

    QPushButton applyButton;

    QVBoxLayout mainLayout;

public:
    GamePage(QWidget *parent = nullptr);
};

#endif