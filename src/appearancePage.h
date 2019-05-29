#ifndef APPEARANCEPAGE_H
#define APPEARANCEPAGE_H

#include <map>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

using namespace std;

// forward declarations
class MainWindow;

// global declarations
extern float SCALE_FACTOR;

class AppearancePage : public QWidget
{
    MainWindow *mainWindow;

    map<float /*SCALE_FACTOR*/, string> resolutionTextMap;
    vector<float> scaleFactorVector;

    // when using a layout, objects must be allocated on the heap
    QGroupBox *appearanceGroup;
    QLabel *resolutionLabel;
    QComboBox *resolutionComboBox;
    QHBoxLayout *resolutionLayout;

    QPushButton *applyButton;

    QVBoxLayout *appearanceLayout;
    QVBoxLayout *mainLayout;

public:
    AppearancePage(MainWindow *pMainWindow, QWidget *parent = 0);
    virtual ~AppearancePage();

    void fillResolutionMaps();

    void onApply();
};

#endif