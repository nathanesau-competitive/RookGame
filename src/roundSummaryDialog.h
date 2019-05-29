#ifndef ROUNDSUMMARYDIALOG_H
#define ROUNDSUMMARYDIALOG_H

#include<map>

#include "common.h"

using namespace std;

class RoundSummaryDialog : public ScaledQDialog
{
    ScaledQLabel summaryLabel;

    ScaledQLabel player1ScoreLabel;
    ScaledQLabel player1Score;

    ScaledQLabel player2ScoreLabel;
    ScaledQLabel player2Score;

    ScaledQLabel player3ScoreLabel;
    ScaledQLabel player3Score;

    ScaledQLabel player4ScoreLabel;
    ScaledQLabel player4Score;

    ScaledQPushButton okButton;

public:
    RoundSummaryDialog(QWidget *parent = nullptr);

    void updateScores(map<int, int> roundScores);
};

#endif