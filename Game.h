#pragma once
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Graphics.h"

const int BOARD_SIZE = 9;
const char SYMBOL_X = 'X';
const char SYMBOL_O = 'O';
const int WINNING_COMB[8][3] = {
                        {0,1,2},{0,3,6},{0,4,8},
                        {1,4,7},{2,4,6},{2,5,8},
                        {3,4,5},{6,7,8}
};
class Game {
private:
    char next_symbol;
    char board[BOARD_SIZE];
    int games_played;
 
    void initializeBoard();
    void initializeGame();
    void incrementGamesPlayed();
    
    bool checkWin();
    bool checkTie();
    bool checkCompletion();

public:
    Game();
    int getGamesPlayed();
    char* getBoardArray();
    bool move(int position);
};
