#include "GamePage.h"

GamePage::GamePage(QWidget *parent) : QWidget(parent)
{
    updateGroup = new QGroupBox;
    updateGroup->setTitle("Package selection");

    systemCheckBox = new QCheckBox;
    systemCheckBox->setText("Update system");

    appsCheckBox = new QCheckBox;
    appsCheckBox->setText("Update applications");

    docsCheckBox = new QCheckBox;
    docsCheckBox->setText("Update documentation");

    packageGroup = new QGroupBox;
    packageGroup->setTitle("Existing packages");
    
    auto setupListWidgetItem = [this](QListWidgetItem *item, QString text)
    {
        item = new QListWidgetItem;
        item->setText(text);

        packageList->addItem(item);
    };

    packageList = new QListWidget;
    setupListWidgetItem(qtItem, "Qt");
    setupListWidgetItem(qsaItem, "QSA");
    setupListWidgetItem(teamBuilderItem, "Teambuilder");

    startUpdateButton = new QPushButton;
    startUpdateButton->setText("Start update");

    updateLayout = new QVBoxLayout;
    updateLayout->addWidget(systemCheckBox);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);

    updateGroup = new QGroupBox;
    updateGroup->setLayout(updateLayout);

    packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);

    packageGroup->setLayout(packageLayout);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    
    setLayout(mainLayout);
}

GamePage::~GamePage()
{
}