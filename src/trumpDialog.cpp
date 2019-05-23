#include "card.h"
#include "trumpDialog.h"

TrumpDialogLabel::TrumpDialogLabel(TrumpDialog *parent) : ScaledQLabel(parent)
{
}

void TrumpDialogLabel::mousePressEvent(QMouseEvent *event)
{
    TrumpDialog *parentDialog = dynamic_cast<TrumpDialog *>(parent ());

    parentDialog->onTrumpLabelClicked(this);
}

TrumpDialog::TrumpDialog(int &pSuitSelected, QWidget *parent) : suitSelected(pSuitSelected), ScaledQDialog(parent)
{
    auto setupTrumpLabel = [this](TrumpDialogLabel &label, QString text, QString style, QPoint pos) {
        label.setFont(QFont("Times", 12));
        label.setText(text);
        label.setStyleSheet(style);
        label.setParent(this);
        label.move(pos);
        label.setAlignment(Qt::AlignCenter);
    };

    setupTrumpLabel(redLabel, "Red", "background-color: red", QPoint(25, 25));
    setupTrumpLabel(blackLabel, "Black", "background-color: black; color: white", QPoint(25, 75));
    setupTrumpLabel(greenLabel, "Green", "background-color: green", QPoint(25, 125));
    setupTrumpLabel(yellowLabel, "Yellow", "background-color: yellow", QPoint(25, 175));

    setGeometry(QRect(0, 0, 600, 250));
    setWindowTitle("Choose Trump Suit...");
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

TrumpDialog::~TrumpDialog()
{
    // todo
}

void TrumpDialog::onTrumpLabelClicked(TrumpDialogLabel *label)
{
    string text = label->text().toStdString();

    if (text == "Black")
    {
        suitSelected = SUIT_BLACK;
    }
    else if (text == "Green")
    {
        suitSelected = SUIT_GREEN;
    }
    else if (text == "Red")
    {
        suitSelected = SUIT_RED;
    }
    else if (text == "Yellow")
    {
        suitSelected = SUIT_YELLOW;
    }

    accept();
}
