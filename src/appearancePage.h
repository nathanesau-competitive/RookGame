#ifndef APPEARANCEPAGE_H
#define APPEARANCEPAGE_H

#include <map>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QWidget>
#include <vector>

using namespace std;

// forward declarations
class MainWindow;

// global declarations
extern float scalefactor;

class AppearancePage : public QWidget
{
    MainWindow *mainWindow;

    map<float /*scalefactor*/, string> resolutionTextMap;
    vector<float> scaleFactorVector;

    QGroupBox resolutionGroup;
    QHBoxLayout resolutionLayout;
    QLabel resolutionLabel;
    QComboBox resolutionComboBox;

    QGroupBox namesGroup;
    QHBoxLayout namesLayout;
    QLabel player1NameLabel;
    QLineEdit player1NameEdit;
    QLabel player2NameLabel;
    QLineEdit player2NameEdit;
    QLabel player3NameLabel;
    QLineEdit player3NameEdit;
    QLabel player4NameLabel;
    QLineEdit player4NameEdit;

    QPushButton applyButton;
    
    QVBoxLayout mainLayout;

public:
    AppearancePage(MainWindow *pMainWindow, QWidget *parent = 0);
    virtual ~AppearancePage();

    void setupResolutionComboBox();

    void onApply();
};

#endif