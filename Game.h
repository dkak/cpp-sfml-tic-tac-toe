#pragma once
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Graphics.h"
#include "GameState.h"

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
    char symbol;
    char board[BOARD_SIZE];
    int games_played;
 
    void initializeBoard();
    void initializeGame();
    void incrementGamesPlayed();
    
    bool hasWon(char symbol);
    bool isCompleted();
    bool isTie();

public:
    Game();
    int getGamesPlayed();
    char* getBoardArray();
    void move(int position);
    GameState getState();
};
