#include "GamePage.h"

// Preferences
//
// - display partner card on hover
// - pick self as partner
// - screen timeout

GamePage::GamePage(QWidget *parent) : QWidget(parent)
{
    systemCheckBox.setText("Update system");
    appsCheckBox.setText("Update applications");
    docsCheckBox.setText("Update documentation");

    updateGroup.setTitle("Package selection");
    updateLayout.addWidget(&systemCheckBox);
    updateLayout.addWidget(&appsCheckBox);
    updateLayout.addWidget(&docsCheckBox);
    updateGroup.setLayout(&updateLayout);

    qtItem.setText("Qt");
    qsaItem.setText("QSA");
    teamBuilderItem.setText("Teambuilder");

    packageGroup.setTitle("Existing packages");
    packageList.addItem(&qtItem);
    packageList.addItem(&qsaItem);
    packageList.addItem(&teamBuilderItem);
    packageLayout.addWidget(&packageList);
    packageGroup.setLayout(&packageLayout);

    applyButton.setText("Apply");

    mainLayout.addWidget(&updateGroup);
    mainLayout.addWidget(&packageGroup);
    mainLayout.addSpacing(12);
    mainLayout.addWidget(&applyButton);
    mainLayout.addStretch(1);
    
    setLayout(&mainLayout);
}
