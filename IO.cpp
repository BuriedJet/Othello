#include "base.h"
#include "extern.h"
#include <iomanip>

string input() //For human input
{
    inputFlag = false;

    ////Echo
    if (modeFlag) cout << "Your Turn:__\b\b";
    else
    {
        if (sideFlag) cout << "Black(X) Turn:__\b\b";
        else cout << "White(X) Turn:__\b\b";
    }

    ////Input conversion
    string input;
    cin >> input;
    if (input.length() == 2)
    {
        input[0] = toupper(input[0]);
        input[1] = toupper(input[1]);
        if (input[0] >= START_COORD_Y&&input[0] <= END_COORD_Y&&input[1] >= START_COORD_X&&input[1] <= END_COORD_X)
        {
            input.assign(input.rbegin(), input.rend());
            inputFlag = true;
        }
        else if (input[0] >= START_COORD_X&&input[0] <= END_COORD_X&&input[1] >= START_COORD_Y&&input[1] <= END_COORD_Y)
        {
            inputFlag = true;
        }
    }
    return input;
}

void output()
{
    SLP(200);
    CLS;
    cout << " ";
    for (int i = 1; i <= SIDE_LENGTH; i++) cout << ' ' << char('@' + i);
    cout << endl;
    char outTmp;
    for (int i = 1; i <= SIDE_LENGTH; i++)
    {
        cout << i;
        for (int j = 1; j <= SIDE_LENGTH; j++)
        {
            switch (board[i][j])
            {
                case Black:
                    outTmp = 'X';
                    break;
                case White:
                    outTmp = 'O';
                    break;
                case Empty:
                    outTmp = ' ';
                    break;
                case Valid:
                    if (assistFlag && ((modeFlag&&sideFlag == userSide) || (!modeFlag))) outTmp = '*';
                    else outTmp = ' ';
                    break;
                default:
                    fatalError(1);
            }
            cout << ' ' << outTmp;
        }
        if (i - SIDE_LENGTH) cout << endl;
    }
    cout << endl << left << "Black(X):" << setw(2) << stoneCount[Black] << "  White(O):" << setw(2) << stoneCount[White] << endl << endl;
}

void getCoord(getType T)
{
    switch (T)
    {
        case Player:
            coord = input();
            inputX = coord[0] - '0';
            inputY = coord[1] - '@';
            break;
        case Computer:
            coord = AI();
            inputX = coord[0] - '0';
            inputY = coord[1] - '0';
            break;
        default:
            fatalError(1);
    }
}
