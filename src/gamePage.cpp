#include "GamePage.h"

// Preferences
//
// - display partner card on hover
// - pick self as partner
// - screen timeout

GamePage::GamePage(QWidget *parent) : QWidget(parent)
{
    systemCheckBox = new QCheckBox;
    systemCheckBox->setText("Update system");

    appsCheckBox = new QCheckBox;
    appsCheckBox->setText("Update applications");

    docsCheckBox = new QCheckBox;
    docsCheckBox->setText("Update documentation");

    updateGroup = new QGroupBox;
    updateGroup->setTitle("Package selection");

    updateLayout = new QVBoxLayout;
    updateLayout->addWidget(systemCheckBox);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);
    updateGroup->setLayout(updateLayout);

    qtItem = new QListWidgetItem;
    qtItem->setText("Qt");

    qsaItem = new QListWidgetItem;
    qsaItem->setText("QSA");

    teamBuilderItem = new QListWidgetItem;
    teamBuilderItem->setText("Teambuilder");

    packageList = new QListWidget;
    packageList->addItem(qtItem);
    packageList->addItem(qsaItem);
    packageList->addItem(teamBuilderItem);

    packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);

    packageGroup = new QGroupBox;
    packageGroup->setTitle("Existing packages");
    packageGroup->setLayout(packageLayout);

    applyButton = new QPushButton;
    applyButton->setText("Apply");

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(applyButton);
    mainLayout->addStretch(1);
    
    setLayout(mainLayout);
}
