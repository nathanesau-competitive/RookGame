#ifndef CARD_H
#define CARD_H

// DO NOT MODIFY
const int SUIT_UNDEFINED = -1;
const int SUIT_BLACK = 0;
const int SUIT_GREEN = 1;
const int SUIT_RED = 2;
const int SUIT_YELLOW = 3;
const int SUIT_SPECIAL = 4;

// DO NOT MODIFY
const int VALUE_UNDEFINED = -1;
const int VALUE_ROOK = 0;
const int VALUE_1 = 1;
const int VALUE_2 = 2;
const int VALUE_3 = 3;
const int VALUE_4 = 4;
const int VALUE_5 = 5;
const int VALUE_6 = 6;
const int VALUE_7 = 7;
const int VALUE_8 = 8;
const int VALUE_9 = 9;
const int VALUE_10 = 10;
const int VALUE_11 = 11;
const int VALUE_12 = 12;
const int VALUE_13 = 13;
const int VALUE_14 = 14;

struct Card
{
    int suit;
    int value;

    Card(int pSuit = SUIT_UNDEFINED, int pValue = VALUE_UNDEFINED);
    bool operator==(const Card &p);
    bool operator!=(const Card &p);

    int getPointValue();
};

struct SuitInfo
{
    int suit;
    int count;
    int totalValue;

    SuitInfo(int pSuit, int pCount = 0, int pTotalValue = 0) : suit(pSuit), count(pCount), totalValue(pTotalValue)
    {
    }

    bool operator==(const SuitInfo &p)
    {
        return p.suit == suit;
    }
};

#endif