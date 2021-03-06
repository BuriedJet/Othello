/*
Achilles
A Powerful Othello AI
By Jet
Version 2.9
*/

#include "elements.h"
#include "Achilles.h"

double Achilles(Board &board, short depth, double alpha, double beta, Coord &bestCoord)
{
    if (board.isWin(~board))
        return BETA - 2000 + 12 * board.isWin(~board) + depth;
    if (board.isWin(!board))
        return ALPHA + 1000 - 12 * board.isWin(!board) - depth;

    if (!depth || !board(Valid) || clock() - startTime > TIME_OUT * CLOCKS_PER_SEC)
        return BoardEval(board);

    double Eval;

    Board mainTmp = board;
    mainTmp.move(board.validCoord[0]);

    Eval = -Achilles(mainTmp, depth - 1, -beta, -alpha, bestCoord);
    if (Eval >= beta)
    {
        if (depth == Game::maxDepth)
            bestCoord = board.validCoord[0];
        return beta;
    }
    if (Eval > alpha)
    {
        alpha = Eval;
        if (depth == Game::maxDepth)
            bestCoord = board.validCoord[0];
    }

    for (size_t i = 1; i < board.validCoord.size(); i++)
    {
        Board tmpBoard = board;
        tmpBoard.move(board.validCoord[i]);

        Eval = -Achilles(tmpBoard, depth - 1, -alpha - MINWINDOW, -alpha, bestCoord);

        if (Eval > alpha&&Eval < beta)
            Eval = -Achilles(tmpBoard, depth - 1, -beta, -alpha - MINWINDOW, bestCoord);

        if (Eval >= beta)
        {
            if (depth == Game::maxDepth)
                bestCoord = board.validCoord[i];
            return beta;
        }
        if (Eval > alpha)
        {
            alpha = Eval;
            if (depth == Game::maxDepth)
                bestCoord = board.validCoord[i];
        }
    }
    return alpha;
}

Coord Hector(Board &board)
{
    srand(unsigned(clock()));
    return board.validCoord[rand()%board.validCoord.size()];
}

Coord CallAI(Board &board)
{
    startTime = clock();

    if (Game::maxDepth == 0 || (Game::randomFlag&&!(rand() % RANDFACTOR)))
        return Hector(board);

    if (Game::finalSearch)
    {
        if (Game::board(Empty) < 16)
        {
            BWFACTOR[Black] = 6.00;
            BWFACTOR[White] = 6.00;
            CNFACTOR[Black] = 5.00;
            CNFACTOR[White] = 6.00;
            DCFACTOR[Black] = 2.00;
            DCFACTOR[White] = 2.00;
            FRFACTOR = 0.10;
            MBFACTOR = 0.20;
            SDFACTOR = 3.33;

            if (Game::board.validCoord.size() > 10)
                Game::maxDepth = 10;
            else if (Game::board(Empty) < 14)
                Game::maxDepth = 13;
            else
                Game::maxDepth = 11;
        }
        else if (Game::board(Empty) < 21)
        {
            if (Game::board(Empty) < 19)
                Game::maxDepth = 10;
            else
                Game::maxDepth = 9;

            BWFACTOR[Black] = 0.14;
            BWFACTOR[White] = 0.14;
            CNFACTOR[Black] = 9.00;
            CNFACTOR[White] = 9.50;
            DCFACTOR[Black] = 3.82;
            DCFACTOR[White] = 3.82;
            FRFACTOR = 0.64;
            MBFACTOR = 0.79;
            SDFACTOR = 3.33;
            CRFACTOR = 0.01;

            if (Game::board.validCoord.size() > 10)
                Game::maxDepth = 9;
        }
        else
        {
            BWFACTOR[Black] = 0.14;
            BWFACTOR[White] = 0.14;
            CNFACTOR[Black] = 9.00;
            CNFACTOR[White] = 9.50;
            DCFACTOR[Black] = 3.82;
            DCFACTOR[White] = 3.82;
            FRFACTOR = 0.64;
            MBFACTOR = 0.79;
            SDFACTOR = 3.33;
            CRFACTOR = 0.05;
            if (Game::board.validCoord.size() > 8)
                Game::maxDepth = 7;
        }
    }
    else
    {
        BWFACTOR[Black] = 0.14;
        BWFACTOR[White] = 0.14;
        CNFACTOR[Black] = 9.00;
        CNFACTOR[White] = 9.50;
        DCFACTOR[Black] = 3.82;
        DCFACTOR[White] = 3.82;
        FRFACTOR = 0.64;
        MBFACTOR = 0.79;
        SDFACTOR = 3.33;
        CRFACTOR = 0.05;
    }

    Game::AchillesReturn = Achilles(board);

    assert(Game::board.isValid(Game::inputCoord, ~board));

    return Game::inputCoord;
}

double BoardEval(Board &board)
{
    //Evaluation Based on Character Value
    double CharaEval;

    double&& myChara = board.allEvalFor(~board);
    double&& opChara = board.allEvalFor(!board);

    CharaEval = myChara - opChara;


    //Evaluation Based on Stone Rate
    double BWRateEval;

    short&& myStoneCount = board(~board);
    short&& opStoneCount = board(!board);

    if (myStoneCount > opStoneCount)
        BWRateEval = 100.0 * myStoneCount / (myStoneCount + opStoneCount);
    else if (myStoneCount < opStoneCount)
        BWRateEval = -100.0 * opStoneCount / (myStoneCount + opStoneCount);
    else BWRateEval = 0;


    //Evaluation Based on Stone Frontier Rate
    double FrontierRateEval;

    size_t&& myFrontierCount = board.sideFrontier[~board].size();
    size_t&& opFrontierCount = board.sideFrontier[!board].size();

    if (myFrontierCount > opFrontierCount)
        FrontierRateEval = -100.0 * myFrontierCount / (myFrontierCount + opFrontierCount);
    else if (myFrontierCount < opFrontierCount)
        FrontierRateEval = 100.0 * opFrontierCount / (myFrontierCount + opFrontierCount);
    else FrontierRateEval = 0;


    //Evaluation Based on Corner Stone Count
    double CornerEval;

    short myCornerCount =
        (board[1][1].stat == Status(~board)) +
        (board[1][8].stat == Status(~board)) +
        (board[8][1].stat == Status(~board)) +
        (board[8][8].stat == Status(~board));

    short opCornerCount =
        (board[1][1].stat == Status(!board)) +
        (board[1][8].stat == Status(!board)) +
        (board[8][1].stat == Status(!board)) +
        (board[8][8].stat == Status(!board));

    CornerEval = 25 * (myCornerCount - opCornerCount);


    //Evaluation Based on Dangerous Corner-Beside-Stone Count
    double DCornerEval;

    short myDCornerCount =
        (board[1][1].stat >= Empty) && (board[1][2].stat == Status(~board)) +
        (board[1][1].stat >= Empty) && (board[2][2].stat == Status(~board)) +
        (board[1][1].stat >= Empty) && (board[2][1].stat == Status(~board)) +
        (board[1][8].stat >= Empty) && (board[1][7].stat == Status(~board)) +
        (board[1][8].stat >= Empty) && (board[2][7].stat == Status(~board)) +
        (board[1][8].stat >= Empty) && (board[2][8].stat == Status(~board)) +
        (board[8][1].stat >= Empty) && (board[8][2].stat == Status(~board)) +
        (board[8][1].stat >= Empty) && (board[7][1].stat == Status(~board)) +
        (board[8][1].stat >= Empty) && (board[7][2].stat == Status(~board)) +
        (board[8][8].stat >= Empty) && (board[8][7].stat == Status(~board)) +
        (board[8][8].stat >= Empty) && (board[7][7].stat == Status(~board)) +
        (board[8][8].stat >= Empty) && (board[7][8].stat == Status(~board));

    short opDCornerCount =
        (board[1][1].stat >= Empty) && (board[1][2].stat == Status(!board)) +
        (board[1][1].stat >= Empty) && (board[2][2].stat == Status(!board)) +
        (board[1][1].stat >= Empty) && (board[2][1].stat == Status(!board)) +
        (board[1][8].stat >= Empty) && (board[1][7].stat == Status(!board)) +
        (board[1][8].stat >= Empty) && (board[2][7].stat == Status(!board)) +
        (board[1][8].stat >= Empty) && (board[2][8].stat == Status(!board)) +
        (board[8][1].stat >= Empty) && (board[8][2].stat == Status(!board)) +
        (board[8][1].stat >= Empty) && (board[7][1].stat == Status(!board)) +
        (board[8][1].stat >= Empty) && (board[7][2].stat == Status(!board)) +
        (board[8][8].stat >= Empty) && (board[8][7].stat == Status(!board)) +
        (board[8][8].stat >= Empty) && (board[7][7].stat == Status(!board)) +
        (board[8][8].stat >= Empty) && (board[7][8].stat == Status(!board));


    DCornerEval = -12.5 * (myDCornerCount - opDCornerCount);

    double sideEval;

    short mySideCount = 0, opSideCount = 0;

    if (board[1][1].stat == Status(~board))
    {
        for (int i = 1; i <= 8; i++)
        {
            if (board[1][i].stat == Status(~board))
                mySideCount += i;
            else
                break;
        }
        for (int i = 1; i <= 8; i++)
        {
            if (board[i][1].stat == Status(~board))
                mySideCount += i;
            else
                break;
        }
    }
    else if (board[1][1].stat == Status(!board))
    {
        for (int i = 1; i <= 8; i++)
        {
            if (board[1][i].stat == Status(!board))
                opSideCount += i;
            else
                break;
        }
        for (int i = 1; i <= 8; i++)
        {
            if (board[i][1].stat == Status(!board))
                opSideCount += i;
            else
                break;
        }
    }

    if (board[1][8].stat == Status(~board))
    {
        for (int i = 1; i <= 8; i++)
        {
            if (board[i][8].stat == Status(~board))
                mySideCount += i;
            else
                break;
        }
        for (int i = 8; i >= 1; i--)
        {
            if (board[1][i].stat == Status(~board))
                mySideCount += 9 - i;
            else
                break;
        }
    }
    else if (board[1][8].stat == Status(!board))
    {
        for (int i = 1; i <= 8; i++)
        {
            if (board[i][8].stat == Status(!board))
                opSideCount += i;
            else
                break;
        }
        for (int i = 8; i >= 1; i--)
        {
            if (board[1][i].stat == Status(!board))
                opSideCount += 9 - i;
            else
                break;
        }
    }

    if (board[8][8].stat == Status(~board))
    {
        for (int i = 8; i >= 1; i--)
        {
            if (board[8][i].stat == Status(~board))
                mySideCount += 9 - i;
            else
                break;
        }
        for (int i = 8; i >= 1; i--)
        {
            if (board[i][8].stat == Status(~board))
                mySideCount += 9 - i;
            else
                break;
        }
    }
    else if (board[8][8].stat == Status(!board))
    {
        for (int i = 8; i >= 1; i--)
        {
            if (board[8][i].stat == Status(!board))
                opSideCount += 9 - i;
            else
                break;
        }
        for (int i = 8; i >= 1; i--)
        {
            if (board[i][8].stat == Status(!board))
                opSideCount += 9 - i;
            else
                break;
        }
    }

    if (board[8][1].stat == Status(~board))
    {
        for (int i = 8; i >= 1; i--)
        {
            if (board[i][1].stat == Status(~board))
                mySideCount += 9 - i;
            else
                break;
        }
        for (int i = 1; i <= 8; i++)
        {
            if (board[8][i].stat == Status(~board))
                mySideCount += i;
            else
                break;
        }
    }
    else if (board[8][1].stat == Status(!board))
    {
        for (int i = 8; i >= 1; i--)
        {
            if (board[i][1].stat == Status(!board))
                opSideCount += 9 - i;
            else
                break;
        }
        for (int i = 1; i <= 8; i++)
        {
            if (board[8][i].stat == Status(!board))
                opSideCount += i;
            else
                break;
        }
    }

    sideEval = 2.5 * (mySideCount - opSideCount);

    //Evaluation Based on Mobility
    double MobEval;

    short myValidCount = board.validCountFor[~board];
    short opValidCount = board.validCountFor[!board];

    if (!opValidCount)
        MobEval = 150;
    else if (!myValidCount)
        MobEval = -450;
    else if (myValidCount > opValidCount)
        MobEval = (100.0 * myValidCount) / (myValidCount + opValidCount);
    else if (myValidCount < opValidCount)
        MobEval = -(100.0 * opValidCount) / (myValidCount + opValidCount);
    else MobEval = 0;



    //Weighed Evaluation
        double Eval =
        (BWFACTOR[~board] * BWRateEval) +
        (CNFACTOR[~board] * CornerEval) +
        (DCFACTOR[~board] * DCornerEval) +
        (SDFACTOR*sideEval) +
        (MBFACTOR*MobEval) +
        (FRFACTOR*FrontierRateEval) +
        (CRFACTOR*CharaEval);

    return Eval;
    //return board(~board);

}
