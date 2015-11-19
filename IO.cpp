#include "elements.h"
#include <sstream>
#include <algorithm>

int mouseMove = 0;
short xBuffer[10], yBuffer[10];
bool mouseInputAvalable = false;

extern bool UIFlag, debugFlag, inputFlag, assistFlag, AIFlag, playerSide, saveError;
extern Board gameBoard;
extern Coord inputCoord;
extern short maxDepth, diff;

extern void menu();
extern Coord AI(Board &board, short depth);
extern void fatalError(unsigned ErrorCode);
Coord keyboardInput(string &input);

extern int screenSize;

void printVersion()
{
    cout << "Othello Main Version " << MAIN_VERSION << endl;
    cout << "AI Version " << AI_VERSION << endl << endl ;
    cout << "Copyleft 2015" << endl;
    cout << endl << endl << endl;
}

// Mouse Callback
void mouseKey(int button, int state, int x, int y){
    if (!mouseInputAvalable) return;
    if (state != GLUT_DOWN) return;
    yBuffer[mouseMove] = (x / (screenSize / SIDE_LENGTH)) + 1;
    xBuffer[mouseMove] = (y / (screenSize / SIDE_LENGTH)) + 1;
    mouseMove++;
    mouseInputAvalable = false;
    return;
}

//For Mouse Input
Coord mouseInput()
{
    inputFlag = false;
    mouseInputAvalable = true;
    while (mouseMove == 0) SLP(100);
    Coord tmpCoord{xBuffer[mouseMove-1], yBuffer[mouseMove-1]};
    mouseMove--;
    inputFlag = true;
    return tmpCoord;
}

//For Keyboard Input
Coord keyboardInput()
{
    ////Echo
    if (AIFlag == AI_MODE)
        cout << "Your Turn:__\b\b";
    else
    {
        if (gameBoard.sideFlag == Black)
            cout << "Black(X) Turn:__\b\b";
        else
            cout << "White(O) Turn:__\b\b";
    }

    string input;
    cin >> input;

    transform(input.begin(), input.end(), input.begin(), ::toupper);

    if (input == "EXIT") exit(0);
    if (input == "MENU") menu();
    if (input == "SAVE")
    {
        if (saveError = gameBoard.save())
        {
            cout << "Game Successfully Saved!" << endl;
            cout << "Press Any Key to Main Menu..." << endl;

            PAUSE;
            menu();
        }
        else return keyboardInput();
    }

    Coord tmpCoord{};
    inputFlag = false;

    if (input.length() == 2)
    {
        if (input[0] >= START_COORD_Y&&input[0] <= END_COORD_Y&&input[1] >= START_COORD_X&&input[1] <= END_COORD_X)
        {
            input.assign(input.rbegin(), input.rend());
            inputFlag = true;
        }
        else if (input[0] >= START_COORD_X&&input[0] <= END_COORD_X&&input[1] >= START_COORD_Y&&input[1] <= END_COORD_Y)
            inputFlag = true;
        else return tmpCoord;

        tmpCoord.x = input[0] - '0';
        tmpCoord.y = input[1] - '@';
    }
    return tmpCoord;
}

void getCoord(getType T)
{
    switch (T)
    {
        case Player:
            if (UIFlag)
                inputCoord = mouseInput();
            else
                inputCoord = keyboardInput();
            break;
        case Computer:
            inputCoord = AI(gameBoard, maxDepth);
            break;
        default:
            fatalError(1);
    }

    gameBoard.movesRecord.push_back(inputCoord);
}

void loadGame()
{
    ifstream load("Othello.save");
    ifstream hload("Othello.hash");
    ostringstream sload, hsload;
    if (!load||!hload||!sload)
    {
        cout << "Unable to Open Saved File!" << endl;
        cout << "Press Any Key to Main Menu...";
        PAUSE;
        menu();
    }

    hash<string> hashptr;
    hsload << hload.rdbuf();
    sload << load.rdbuf();

    string saveHash = hsload.str();
    string file = sload.str();
    
    ostringstream convert;
    convert << hashptr(file);
    string fileHash = convert.str();

    if (fileHash != saveHash)
    {
        cout << "Saved File Damaged!" << endl;
        cout << "Press Any Key to Main Menu...";
        PAUSE;
        menu();
    }
    load.close();
    hload.close();
    
    load.open("Othello.save");
    cin.rdbuf(load.rdbuf());
    cin >> assistFlag;
    cin >> playerSide;
    cin >> AIFlag;

    int movesCount;
    cin >> movesCount;
    gameBoard.movesRecord.clear();

    for (int i = 0; i < movesCount; i++)
    {
        Coord tmpCoord;
        cin >> tmpCoord.x;
        cin >> tmpCoord.y;
        gameBoard.movesRecord.push_back(tmpCoord);
    }

}