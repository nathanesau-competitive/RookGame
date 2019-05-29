#include <vector>

#include "AppearancePage.h"
#include "mainWindow.h"
#include "utils.h"

using namespace std;

AppearancePage::AppearancePage(MainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                           QWidget(parent)
{
    appearanceGroup = new QGroupBox;
    appearanceGroup->setTitle("Appearance");

    resolutionLabel = new QLabel;
    resolutionLabel->setText("Game Resolution");

    fillResolutionMaps();

    resolutionComboBox = new QComboBox;

    for (auto It = resolutionTextMap.begin(); It != resolutionTextMap.end(); It++)
    {
        resolutionComboBox->addItem(QString::fromStdString(It->second));
    }

    auto It = std::find(scaleFactorVector.begin(), scaleFactorVector.end(), SCALE_FACTOR);

    if (It != scaleFactorVector.end())
    {
        int index = std::distance(scaleFactorVector.begin(), It);
        resolutionComboBox->setCurrentIndex(index);
    }

    resolutionLayout = new QHBoxLayout;
    resolutionLayout->addWidget(resolutionLabel);
    resolutionLayout->addWidget(resolutionComboBox);

    appearanceLayout = new QVBoxLayout;
    appearanceLayout->addLayout(resolutionLayout);

    appearanceGroup = new QGroupBox;
    appearanceGroup->setLayout(appearanceLayout);

    applyButton = new QPushButton;
    applyButton->setText("Apply");

    QObject::connect(applyButton, &QAbstractButton::clicked, this, &AppearancePage::onApply);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(appearanceGroup);
    mainLayout->addStretch(1);
    mainLayout->addWidget(applyButton);

    setLayout(mainLayout);
}

AppearancePage::~AppearancePage()
{
}

void AppearancePage::fillResolutionMaps()
{
    float minScaleFactor = 0.5F;
    float currentScaleFactor = SCALE_FACTOR;
    float maxScaleFactor = Utils::Ui::getBestScaleFactor();

    int scaleFactorIndex = 0;

    for(int i = minScaleFactor * 10; i <= maxScaleFactor * 10; i++) // 0.5F, 0.6F, ...
    {
        float scaleFactor = i / 10.0F;
        QSize resolution = Utils::Ui::getResolution(scaleFactor);
        string choice = to_string(resolution.width()) + "x" + to_string(resolution.height());
        choice += " (" + to_string(i/10) + "." + to_string(i % 10) + "x)";
        resolutionTextMap[scaleFactor] = choice;
        scaleFactorVector.push_back(scaleFactor);

        scaleFactorIndex++;
    }
}

void AppearancePage::onApply()
{
    int index = resolutionComboBox->currentIndex();
    float factor = scaleFactorVector[index];

    if (factor != SCALE_FACTOR)
    {
        SCALE_FACTOR = factor;
        mainWindow->rescale();
    }
}