/*
Othello For Term Task
Version 0.9.3
*/
#include "base.h"
#include "declaration.h"

int main()
{
    init();
    othelloMain();
    PAUSE;
}

void othelloMain()
{
    output();
    while (gameBoard.statusCount[Empty] && passCount < 2 && gameBoard.statusCount[Black] && gameBoard.statusCount[White])
    {
        ////No-valid situation handle
        if (!gameBoard.statusCount[Valid])
        {
            if (modeFlag == NON_AI_MODE || (modeFlag == AI_MODE &&sideFlag == playerSide)) cout << "No Possible Move, Enter to Pass!";
            else cout << "Computer Passed, Enter to Your Turn!";
            PAUSE;
            passCount++;
            sideFlag ^= 1;
            setValid(gameBoard, sideFlag);
            count(gameBoard);
            continue;
        }

        ////Get input
        if (modeFlag == NON_AI_MODE || sideFlag == playerSide)
        {
            getCoord(Player);
            while (!inputFlag || gameBoard.cell[inputCoord.x][inputCoord.y].stat != Valid)
            {
                if (inputFlag) cout << "Invalid Position!" << endl;
                else cout << "Invalid Input!" << endl;
                getCoord(Player);
            }
        }
        else getCoord(Computer);

        ////Refresh board
        move(gameBoard, inputCoord, sideFlag);
        sideFlag ^= 1;
        setValid(gameBoard, sideFlag);
        count(gameBoard);
        output();
        passCount = 0;
    }
    judge();
}