/*
AI by Jet
Version 1.0
*/

//Make Pass
//C-squares and X-squares Awareness
//Corner Tendency
//Even Block Estimate
//Position Estimate
//Mobility Significance
#include <cmath>

#include "elements.h"
#include "AIbase.h"
#include <algorithm>

extern short maxDepth;
extern bool debugFlag;
extern Board gameBoard;
extern aiType AIType;

extern void fatalError(unsigned ErrorCode);

double AlphaBetaAI(Board &board, short depth, double alpha, double beta, Coord &bestCoord)
{
    if (!depth)
        return BoardEval(board);

    double Eval;
    for (int i = 0; i < board.validCoord.size(); i++)
    {
        Board tmpBoard = board;
        tmpBoard.move(board.validCoord[i]);
        Eval = -AlphaBetaAI(tmpBoard, depth - 1, -beta, -alpha, bestCoord);
        if (Eval >= beta)
        {
            if (depth == maxDepth)
                bestCoord = board.validCoord[i];
            return beta;
        }
        if (Eval > alpha)
        {
            alpha = Eval;
            if (depth == maxDepth)
                bestCoord = board.validCoord[i];
        }
    }
    return alpha;
}

Coord RandomAI(Board &board)
{
    random_shuffle(board.validCoord.begin(), board.validCoord.end());
    return board.validCoord[0];
}

Coord JetAI(Board &board)
{
    Board *tmpBoard = new Board[board.statusCount[Valid]];

    for (int i = 0; i < board.statusCount[Valid]; i++)
    {
        tmpBoard[i] = board;
        tmpBoard[i].move(board.validCoord[i]);
        board.validCoord[i].value = BoardEval(tmpBoard[i]);
    }

    delete[] tmpBoard;

    sort(board.validCoord.begin(), board.validCoord.end(), rcmpCoordV);

    return board.validCoord[0];

}

Coord AI(Board &board, short depth)
{
    switch (AIType)
    {
        case Random:
            return RandomAI(board);
        case Jet:
            return JetAI(board);
        case AB:
            Coord bestCoord;
            AlphaBetaAI(board, depth, ALPHA, BETA, bestCoord);
            return bestCoord;
        default:
            fatalError(1);
    }
}

double BoardEval(Board &board)
{
    //Evaluation Based on Character Value
    double CharaEval;

    double myChara = board.allEval(board.sideFlag);
    double opChara = board.allEval(!board.sideFlag);

    CharaEval = myChara - opChara;


    //Evaluation Based on Stone Rate
    double BWRateEval;

    short myStoneCount = board.statusCount[board.sideFlag];
    short opStoneCount = board.statusCount[!board.sideFlag];

    if (myStoneCount > opStoneCount)
        BWRateEval = 100.0 * myStoneCount / (myStoneCount + opStoneCount);
    else if (myStoneCount < opStoneCount)
        BWRateEval = -100.0 * opStoneCount / (myStoneCount + opStoneCount);
    else BWRateEval = 0;


    //Evaluation Based on Stone Frontier Rate
    double FrontierRateEval;

    short myFrontierCount = board.frontierCount(board.sideFlag);
    short opFrontierCount = board.frontierCount(!board.sideFlag);

    if (myFrontierCount > opFrontierCount)
        FrontierRateEval = -100.0 * myFrontierCount / (myFrontierCount + opFrontierCount);
    else if (myFrontierCount < opFrontierCount)
        FrontierRateEval = 100.0 * opFrontierCount / (myFrontierCount + opFrontierCount);
    else FrontierRateEval = 0;


    //Evaluation Based on Corner Stone Count
    double CornerEval;

    short myCornerCount =
        (board[1][1].stat == status(board.sideFlag)) +
        (board[1][SIDE_LENGTH].stat == status(board.sideFlag)) +
        (board[SIDE_LENGTH][1].stat == status(board.sideFlag)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat == status(board.sideFlag));

    short opCornerCount =
        (board[1][1].stat == status(!board.sideFlag)) +
        (board[1][SIDE_LENGTH].stat == status(!board.sideFlag)) +
        (board[SIDE_LENGTH][1].stat == status(!board.sideFlag)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat == status(!board.sideFlag));

    CornerEval = 25 * (myCornerCount - opCornerCount);


    //Evaluation Based on Dangerous Corner-Beside-Stone Count
    double DCornerEval;

    short myDCornerCount =
        (board.cell[1][1].stat >= Empty) && (board.cell[1][2].stat == status(board.sideFlag)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][2].stat == status(board.sideFlag)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][1].stat == status(board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[1][SIDE_LENGTH - 1].stat == status(board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[2][SIDE_LENGTH - 1].stat == status(board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[2][SIDE_LENGTH].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH][2].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][1].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][2].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH][SIDE_LENGTH - 1].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][SIDE_LENGTH - 1].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][SIDE_LENGTH].stat == status(board.sideFlag));

    short opDCornerCount =
        (board.cell[1][1].stat >= Empty) && (board.cell[1][2].stat == status(!board.sideFlag)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][2].stat == status(!board.sideFlag)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][1].stat == status(!board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[1][SIDE_LENGTH - 1].stat == status(!board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[2][SIDE_LENGTH - 1].stat == status(!board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[2][SIDE_LENGTH].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH][2].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][1].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][2].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH][SIDE_LENGTH - 1].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][SIDE_LENGTH - 1].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][SIDE_LENGTH].stat == status(!board.sideFlag));


    DCornerEval = -12.5 * (myDCornerCount - opDCornerCount);


    //Evaluation Based on Mobility
    double MobEval;

    short myValidCount = board.countValidFor(board.sideFlag);
    short opValidCount = board.countValidFor(!board.sideFlag);

    if (myValidCount > opValidCount)
        MobEval = (100.0 * myValidCount) / (myValidCount + opValidCount);
    else if (myValidCount < opValidCount)
        MobEval = -(100.0 * opValidCount) / (myValidCount + opValidCount);
    else MobEval = 0;

    int loseFlag = 0;
    if (board.statusCount[board.sideFlag] == 0)
        loseFlag = -1;
    else if (board.statusCount[!board.sideFlag] == 0)
        loseFlag = 1;

    //Weighed Evaluation
    double Eval =
        (8 * BWRateEval) +
        (800 * CornerEval) +
        (380 * DCornerEval) +
        (80 * MobEval) +
        (70 * FrontierRateEval) +
        (9 * CharaEval) +
        (100000 * loseFlag);

    if (debugFlag)
    {
        cout << "Classic Eval:" << endl;
        cout << "BWRateEval\t" << BWRateEval << endl;
        cout << "CornerEval\t" << CornerEval << endl;
        cout << "DCornerEval\t" << DCornerEval << endl;
        cout << "MobilityEval\t" << MobEval << endl;
        cout << "FRTRRateEval\t" << FrontierRateEval << endl;
        cout << "CharaEval\t" << CharaEval << endl << endl;
        cout << "ClassicEval\t" << Eval << endl << endl;
    }

    return Eval;

}


bool cmpBoard(const Board &A, const Board &B) { return A > B; }
bool rcmpBoard(const Board &A, const Board &B) { return A < B; }
bool cmpCoordV(const Coord &A, const Coord &B) { return A.value > B.value; }
bool rcmpCoordV(const Coord &A, const Coord &B) { return A.value < B.value; }
bool cmpCoordC(const Coord &A, const Coord &B) { return A.chara > B.chara; }
bool rcmpCoordC(const Coord &A, const Coord &B) { return A.chara < B.chara; }
