#ifndef APPEARANCEPAGE_H
#define APPEARANCEPAGE_H

#include <map>
#include <QCheckBox>
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
    map<int, float /*scalefactor*/> scaleFactorMap;

    QGroupBox *resolutionGroup;
    QHBoxLayout *resolutionLayout;
    QLabel *resolutionLabel;
    QComboBox *resolutionComboBox;

    QGroupBox *namesGroup;
    QVBoxLayout *namesLayout;
    QLabel *player1NameLabel;
    QLineEdit *player1NameEdit;
    QLabel *player2NameLabel;
    QLineEdit *player2NameEdit;
    QLabel *player3NameLabel;
    QLineEdit *player3NameEdit;
    QLabel *player4NameLabel;
    QLineEdit *player4NameEdit;

    QGroupBox *hudGroup;
    QVBoxLayout *hudLayout;
    QCheckBox *showNameTagsBox;
    QCheckBox *showPartnerToolTipBox;

    QGroupBox *screenGroup;
    QVBoxLayout *screenLayout;
    QLineEdit *screenWidthLineEdit;
    QLineEdit *screenHeightLineEdit;

    QPushButton *applyButton;
    
    QVBoxLayout *mainLayout;

public:
    AppearancePage(MainWindow *pMainWindow, QWidget *parent = 0);

private:
    void onApply();

    void applyResolution();
    void applyPlayerNames();
    void applyHUD();
    void applyScreenDimensions();
};

#endif