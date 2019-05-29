#include <string>
#include <QPoint>
#include <QString>

#include "roundSummaryDialog.h"
#include "player.h"

using namespace std;

RoundSummaryDialog::RoundSummaryDialog(QWidget *parent) : ScaledQDialog(true, parent)
{
    auto setupLabel = [this](ScaledQLabel *label, QString text, QSize size, QPoint pos) {
        label->setParent(this);
        label->setText(text);
        label->setFont(QFont("Times", 10));
        label->resize(size.width(), size.height());
        label->move(pos);
    };

    summaryLabel.setParent(this);
    summaryLabel.setText("Scores for this round...");
    summaryLabel.setFont(QFont("Times", 12, QFont::Weight::Bold));
    summaryLabel.resize(250, 25);
    summaryLabel.move({25, 25});

    setupLabel(&player1ScoreLabel, "Player 1: ", {100, 25}, {25, 75});
    setupLabel(&player1Score, "", {100, 25}, {125, 75});
    setupLabel(&player2ScoreLabel, "Player 2: ", {100, 25}, {25, 100});
    setupLabel(&player2Score, "", {100, 25}, {125, 100});
    setupLabel(&player3ScoreLabel, "Player 3: ", {100, 25}, {25, 125});
    setupLabel(&player3Score, "", {100, 25}, {125, 125});
    setupLabel(&player4ScoreLabel, "Player 4: ", {100, 25}, {25, 150});
    setupLabel(&player4Score, "", {100, 25}, {125, 150});

    okButton.setParent(this);
    okButton.setText("OK");
    okButton.setFont(QFont("Times", 10));
    okButton.resize(50, 25);
    okButton.move({400, 200});

    QObject::connect(&okButton, &QPushButton::pressed, this, &RoundSummaryDialog::accept);

    resize(500, 250);
    setWindowTitle("Round summary");
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":rookicon.gif"));
    setStyleSheet("background-color: white");
}

void RoundSummaryDialog::updateScores(map<int, int> roundScores)
{
    auto updateLabel = [this](ScaledQLabel *label, int score) {
        string prefix = "";
        if (score > 0)
            prefix = "+";
        else if (score < 0)
            prefix = "-";

        string text = prefix + to_string(score);
        label->setText(QString::fromStdString(text));
    };

    updateLabel(&player1Score, roundScores[PLAYER_1]);
    updateLabel(&player2Score, roundScores[PLAYER_2]);
    updateLabel(&player3Score, roundScores[PLAYER_3]);
    updateLabel(&player4Score, roundScores[PLAYER_4]);
}