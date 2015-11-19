#ifndef ELMTS_H
#define ELMTS_H

#include "base.h"

enum getType { Player, Computer };
enum status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
                                               //White=false & Black=true

enum aiType { Random, Jet, AB };

struct Coord
{
    short x;
    short y;
    short chara;    //Characteristic Value (Fixed to Position)
    double value;    //Result of Evaluate (Related to Situation)
};

struct Cell
{
    Coord pos;
    status stat;
};

class Board
{
public:
    Cell cell[SAFE_LENGTH][SAFE_LENGTH];
    vector<Coord> validCoord;
    vector<Coord> movesRecord;
    short statusCount[4];
    double vValue;
    double aValue[2];
    bool sideFlag;

public:
    Board();

    void operator =(Board &board);
    bool operator >(const Board &board)const;
    bool operator <(const Board &board)const;
    bool operator ==(const Board &board)const;
    bool operator >=(const Board &board)const;
    bool operator <=(const Board &board)const;
    Cell* operator [](int i);

    void clear();
    void flipSide();
    void count();
    short count(status stat);
    bool isValid(Coord &pos, bool side);
    void setValid();
    void setValidFor(bool side);
    void move(Coord &pos);
    void print();
    double validEval(bool side);
    double allEval(bool side);
    short frontierCount(bool side);

    double aEvalRate(bool side);
    double aEvalDiff(bool side);
    double CountRate(bool side);
    double CountDiff(bool side);
    double frontierCountRate(bool side);
    double frontierCountDiff(bool side);
    short countValidFor(bool side);
    bool save();


    //todo
    void colorReverse();
    void randomize();
};

#endif
