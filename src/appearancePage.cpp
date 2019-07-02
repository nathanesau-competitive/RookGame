#include <QSettings>
#include <vector>

#include "AppearancePage.h"
#include "mainWindow.h"
#include "utils.h"

using namespace std;

AppearancePage::AppearancePage(MainWindow *pMainWindow, QWidget *parent) : mainWindow(pMainWindow),
                                                                           QWidget(parent)
{
    resolutionLabel = new QLabel;
    resolutionLabel->setText("Game Resolution");

    // setup maps

    float minScaleFactor = 0.5F;
    float currentScaleFactor = scalefactor;
    float maxScaleFactor = Utils::Ui::getBestScaleFactor();

    for (int i = minScaleFactor * 10; i <= maxScaleFactor * 10; i++) // 0.5F, 0.6F, ...
    {
        int index = i - minScaleFactor * 10;
        float scaleFactor = i / 10.0F;
        scaleFactorMap[index] = scaleFactor;

        QSize resolution = Utils::Ui::getResolution(scaleFactor);
        string choice = to_string(resolution.width()) + "x" + to_string(resolution.height());
        choice += " (" + to_string(i / 10) + "." + to_string(i % 10) + "x)";
        resolutionTextMap[scaleFactor] = choice;
    }

    // resolutionComboBox

    resolutionComboBox = new QComboBox;

    for (auto It = resolutionTextMap.begin(); It != resolutionTextMap.end(); It++)
    {
        resolutionComboBox->addItem(QString::fromStdString(It->second));
    }

    for (auto It = scaleFactorMap.begin(); It != scaleFactorMap.end(); It++)
    {
        if (It->second == scalefactor)
        {
            resolutionComboBox->setCurrentIndex(It->first);
            break;
        }
    }

    // player names

    player1NameLabel = new QLabel;
    player1NameLabel->setText("Player 1");

    player2NameLabel = new QLabel;
    player2NameLabel->setText("Player 2");

    player3NameLabel = new QLabel;
    player3NameLabel->setText("Player 3");

    player4NameLabel = new QLabel;
    player4NameLabel->setText("Player 4");

    auto setupLineEdit = [this](QLineEdit *lineEdit, QString text) {
        lineEdit->setText(text);
    };

    map<int, string> playerNames = Utils::Db::readPlayerNamesFromDb();

    player1NameEdit = new QLineEdit;
    setupLineEdit(player1NameEdit, QString::fromStdString(playerNames[PLAYER_1]));

    player2NameEdit = new QLineEdit;
    setupLineEdit(player2NameEdit, QString::fromStdString(playerNames[PLAYER_2]));

    player3NameEdit = new QLineEdit;
    setupLineEdit(player3NameEdit, QString::fromStdString(playerNames[PLAYER_3]));

    player4NameEdit = new QLineEdit;
    setupLineEdit(player4NameEdit, QString::fromStdString(playerNames[PLAYER_4]));

    resolutionGroup = new QGroupBox;
    resolutionGroup->setTitle("Resolution");

    resolutionLayout = new QHBoxLayout;
    resolutionLayout->addWidget(resolutionLabel);
    resolutionLayout->addWidget(resolutionComboBox);
    resolutionGroup->setLayout(resolutionLayout);

    namesGroup = new QGroupBox;
    namesGroup->setTitle("Names");

    namesLayout = new QVBoxLayout;
    namesLayout->addWidget(player1NameLabel);
    namesLayout->addWidget(player1NameEdit);
    namesLayout->addWidget(player2NameLabel);
    namesLayout->addWidget(player2NameEdit);
    namesLayout->addWidget(player3NameLabel);
    namesLayout->addWidget(player3NameEdit);
    namesLayout->addWidget(player4NameLabel);
    namesLayout->addWidget(player4NameEdit);
    namesGroup->setLayout(namesLayout);

    // name tags

    showNameTagsBox = new QCheckBox;
    showNameTagsBox->setText("Show name tags");
    showNameTagsBox->setChecked(Utils::Db::readShowNameTagsFromDb());
    
    tagsGroup = new QGroupBox;
    tagsGroup->setTitle("Tags");

    tagsLayout = new QVBoxLayout;
    tagsLayout->addWidget(showNameTagsBox);
    tagsGroup->setLayout(tagsLayout);

    applyButton = new QPushButton;
    applyButton->setText("Apply");
    QObject::connect(applyButton, &QAbstractButton::clicked, this, &AppearancePage::onApply);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(resolutionGroup);
    mainLayout->addWidget(namesGroup);
    mainLayout->addWidget(tagsGroup);
    mainLayout->addStretch(1);
    mainLayout->addWidget(applyButton);

    setLayout(mainLayout);
}

void AppearancePage::onApply()
{
    applyResolution();
    applyPlayerNames();
    applyNameTags();
}

void AppearancePage::applyResolution()
{
    int index = resolutionComboBox->currentIndex();
    float factor = scaleFactorMap[index];

    if (factor == scalefactor)
        return;

    scalefactor = factor;
    Utils::Db::writeScaleFactorToDb(scalefactor);

    mainWindow->rescale();
}

void AppearancePage::applyPlayerNames()
{
    map<int, string> playerNames;

    playerNames[PLAYER_1] = player1NameEdit->text().toStdString();
    playerNames[PLAYER_2] = player2NameEdit->text().toStdString();
    playerNames[PLAYER_3] = player3NameEdit->text().toStdString();
    playerNames[PLAYER_4] = player4NameEdit->text().toStdString();
    Utils::Db::writePlayerNamesToDb(playerNames);

    mainWindow->updatePlayerNames(playerNames);
}

void AppearancePage::applyNameTags()
{
    bool showNameTags = showNameTagsBox->isChecked();
    Utils::Db::writeShowNameTagsToDb(showNameTags);

    mainWindow->updateNameTags(showNameTags);
}