#include "Game.h"
Game::Game()
{
    cout << "Please enter 0 or 1 to choose the mode.\n0 means player vs player and 1 means player vs computer." << endl;
    cin >> Mode;
    while (Mode != 0 && Mode != 1)
    {
        cout << "invalid value for mode. Please try again!\n";
        cin >> Mode;
    }
    cout << "Please enter the grid size from 3 to 9:" << endl;
    cin >> Size;
    while (Size < 3 || Size>9)
    {
        cout << "invalid value for grid size. Please try again!\n";
        cin >> Size;
    }
    Board = vector<vector<char>>(Size, vector<char>(Size, '.'));
}

void Game::Print()
{
    for (int r = 0;r < Size;r++)
    {
        for (int c = 0;c < Size;c++)
        {
            cout << Board[r][c] << " ";
        }
        cout << endl;
    }
}
bool Game::CheckLine(int R, int C,int Dir)
{
    int Row = R, Col = C;
    for (int Step = 0;Step < Size - 1;Step++)
    {
        Row = Row + DirR[Dir];
        Col = Col + DirC[Dir];
        if (Board[Row][Col] != Board[R][C])
            return false;
    }
    return true;
}
bool Game::CheckWinner()
{
    if ((Board[0][0]!='.'&&CheckLine(0, 0, 2)) || (Board[0][Size - 1] != '.' && CheckLine(0, Size - 1, 3)))
        return true;
    for (int i = 0;i < Size;i++)
    {
        if ((Board[i][0] != '.' && CheckLine(i, 0, 0)) || (Board[0][i] != '.' && CheckLine(0, i, 1)))
            return true;
    }
    return false;
}
bool Game::Tie()
{
    for (int i = 0;i < Size;i++)
        for (int j = 0;j < Size;j++)
        {
            if (Board[i][j] == '.')
                return false;
        }
    return true;
}
Move Game::minimax(bool IsMax = true, int Alpha=INT_MIN, int Beta=INT_MAX)
{
    Move BestMove;
    if (CheckWinner())
    {
        if (IsMax)
            BestMove.Score = -1;
        else
            BestMove.Score = 1;
        return BestMove;
    }
    if (Tie())
    {
        BestMove.Score = 0;
        return BestMove;
    }
    bool BreakOuterLoop = false;
    BestMove.Score = (IsMax ? -2 : 2);
    for (int i = 0;i < Size;i++)
    {
        for (int j = 0;j < Size;j++)
        {
            if (Board[i][j] == '.')
            {
                Board[i][j] = (IsMax ? 'o' : 'x');
                Move Check = minimax(!IsMax,Alpha,Beta);
                Board[i][j] = '.';
                if (IsMax)
                {
                    if (Check.Score > BestMove.Score)
                    {
                        BestMove.Score = Check.Score;
                        BestMove.Row = i;
                        BestMove.Col = j;
                    }
                    Alpha = Alpha > Check.Score ? Alpha : Check.Score;
                    if (Alpha >= Beta)
                    {
                        BreakOuterLoop = true;
                        break;
                    }

                }
                else
                {
                    if (Check.Score < BestMove.Score)
                    {
                        BestMove.Score = Check.Score;
                        BestMove.Row = i;
                        BestMove.Col = j;
                    }
                    Beta = Beta < Check.Score ? Beta : Check.Score;
                    if (Alpha >= Beta)
                    {
                        BreakOuterLoop = true;
                        break;
                    }
                }
            }
        }
        if (BreakOuterLoop)
            break;
    }
    return BestMove;
}
void Game::Play()
{
    cout << "***************Note: the board is one-based.***************" << endl;
    int Cnt = Size * Size;
    bool XTurn = 1;
    if (Mode == 0)
    {
        while (Cnt--)
        {
            if (XTurn)
                cout << "Player x turn. Enter empty location (row,col): ";
            else
                cout << "Player o turn. Enter empty location (row,col): ";
            int Row{ 0 }, Col{ 0 };
            cin >> Row >> Col; //It's one-based.
            while ((Row<1 && Row>Size + 1) || (Col<1 && Col>Size + 1) || Board[Row - 1][Col - 1] != '.')
            {
                cout << "Invalid input. Try again\n";
                if (XTurn)
                    cout << "Player x turn. Enter empty location (row,col): ";
                else
                    cout << "Player o turn. Enter empty location (row,col): ";
                cin >> Row >> Col;
            }
            Row--, Col--;
            XTurn == 1 ? Board[Row][Col] = 'x' : Board[Row][Col] = '0';
            Print();
            if (CheckWinner())
            {
                cout << (Board[Row][Col] == 'x' ? "Player x won\n" : "Player o won\n");
                return;
            }
            XTurn = !XTurn;
        }
        cout << "\nDraw\n";
    }
    else
    {
        int Begin, NumberOfPlays = 0;
        cout << "Please enter 0 or 1 to choose who will begin.\n0 means computer will begin and 1 means you will begin" << endl;
        cin >> Begin;
        while (Begin != 0 && Begin != 1)
        {
            cout << "Invalid input. Please try again!\n";
            cin >> Begin;
        }
        int Row{ 0 }, Col{ 0 };
        while (Cnt--)
        {
            if (Begin)
            {
                cout << "Enter empty location (row,col): ";
                cin >> Row >> Col; //It's one-based.
                while ((Row<1 && Row>Size + 1) || (Col<1 && Col>Size + 1) || Board[Row - 1][Col - 1] != '.')
                {
                    cout << "Invalid input. Try again\n";
                    cout << "Enter empty location (row,col): ";
                    cin >> Row >> Col;
                }
                Row--, Col--;
                Board[Row][Col] = 'x'; //player will always play x.
            }
            else
            {
                cout << endl;
                Move BestMove = minimax();
                Row = BestMove.Row;
                Col = BestMove.Col;
                Board[Row][Col] = 'o';
            }
            Print();
            if (CheckWinner())
            {
                cout << (Board[Row][Col] == 'x' ? "Player won\n" : "AI won\n"); //Remember player will always play x.
                return;
            }
            Begin = !Begin;
        }
        cout << "\nDraw\n";
    }
}