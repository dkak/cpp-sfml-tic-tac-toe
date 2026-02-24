#pragma once
#include <iostream>

#include "Game.h"
#include "Types.h"

class Game {
private:
    char board[Config::BOARD_SIZE];
    char symbol;
    GameStatistics game_stats;
    WinInfo win_info;

    bool isTie();
    bool hasWon(char symbol);
public:
    Game();
    char* getBoardArray();
    GameStatistics getGameStatistics();
    GameState getState();
    WinInfo getWinInfo();
    
    void initializeGame();
    void updateGameStats();
    void move(int position);
};