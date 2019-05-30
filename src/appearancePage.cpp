#include <vector>

#include "AppearancePage.h"
#include "mainWindow.h"
#include "utils.h"

using namespace std;

AppearancePage::AppearancePage(MainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                           QWidget(parent)
{
    resolutionLabel.setText("Game Resolution");

    setupResolutionComboBox();

    auto setupLabel = [this](QLabel *label, QString text) {
        label->setText(text);
    };

    setupLabel(&player1NameLabel, "Player 1");
    setupLabel(&player2NameLabel, "Player 2");
    setupLabel(&player3NameLabel, "Player 3");
    setupLabel(&player4NameLabel, "Player 4");

    resolutionGroup.setTitle("Resolution");
    resolutionLayout.addWidget(&resolutionLabel);
    resolutionLayout.addWidget(&resolutionComboBox);
    resolutionGroup.setLayout(&resolutionLayout);

    namesGroup.setTitle("Names");
    namesLayout.addWidget(&player1NameLabel);
    namesLayout.addWidget(&player1NameEdit);
    namesLayout.addWidget(&player2NameLabel);
    namesLayout.addWidget(&player2NameEdit);
    namesLayout.addWidget(&player3NameLabel);
    namesLayout.addWidget(&player3NameEdit);
    namesLayout.addWidget(&player4NameLabel);
    namesLayout.addWidget(&player4NameEdit);
    namesGroup.setLayout(&namesLayout);

    applyButton.setText("Apply");
    QObject::connect(&applyButton, &QAbstractButton::clicked, this, &AppearancePage::onApply);

    mainLayout.addWidget(&resolutionGroup);
    mainLayout.addWidget(&namesGroup);
    mainLayout.addStretch(1);
    mainLayout.addWidget(&applyButton);

    setLayout(&mainLayout);
}

AppearancePage::~AppearancePage()
{
}

void AppearancePage::setupResolutionComboBox()
{
    // 1. RESOLUTION TEXT MAP, SCALE FACTOR VECTOR
    float minScaleFactor = 0.5F;
    float currentScaleFactor = scalefactor;
    float maxScaleFactor = Utils::Ui::getBestScaleFactor();

    int scaleFactorIndex = 0;

    for (int i = minScaleFactor * 10; i <= maxScaleFactor * 10; i++) // 0.5F, 0.6F, ...
    {
        float scaleFactor = i / 10.0F;
        QSize resolution = Utils::Ui::getResolution(scaleFactor);
        string choice = to_string(resolution.width()) + "x" + to_string(resolution.height());
        choice += " (" + to_string(i / 10) + "." + to_string(i % 10) + "x)";
        resolutionTextMap[scaleFactor] = choice;
        scaleFactorVector.push_back(scaleFactor);

        scaleFactorIndex++;
    }

    // 2. COMBO BOX
    for (auto It = resolutionTextMap.begin(); It != resolutionTextMap.end(); It++)
    {
        resolutionComboBox.addItem(QString::fromStdString(It->second));
    }

    auto It = std::find(scaleFactorVector.begin(), scaleFactorVector.end(), scalefactor);

    if (It != scaleFactorVector.end())
    {
        int index = std::distance(scaleFactorVector.begin(), It);
        resolutionComboBox.setCurrentIndex(index);
    }
}

void AppearancePage::onApply()
{
    int index = resolutionComboBox.currentIndex();
    float factor = scaleFactorVector[index];

    if (factor != scalefactor)
    {
        scalefactor = factor;
        mainWindow->rescale();
    }
}