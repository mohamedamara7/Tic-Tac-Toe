#ifndef Game_H
#define Game_H
#include <iostream>
#include <vector>
#include "Move.h"
using namespace std;

class Game
{
public:
    vector<vector<char>> Board;
    int Size;
    int Mode; //If mode=0 then it's a player vs payer, if mode=1 then it's a player vs computer.
                 //Right, Down, RightDown, LeftDown
    int DirR[4] = { 0   ,  1  ,     1     ,      1 };
    int DirC[4] = { 1   ,  0  ,     1     ,     -1 };
    Game();
    void Print();
    bool CheckLine(int, int, int);
    bool CheckWinner();
    bool Tie();
    Move minimax(bool , int , int );
    void Play();
};
#endif