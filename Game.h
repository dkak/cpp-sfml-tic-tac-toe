#pragma once
#include <iostream>

#include "Game.h"
#include "Graphics.h"
#include "Types.h"

class Game {
private:
    char board[Config::BOARD_SIZE];
    char symbol;
    GameStats game_stats;
    WinInfo win_info;

public:
    Game();
    char* getBoardArray();
    GameStats getGameStats();
    WinInfo getWinInfo();
    void updateGameStats();
    void initializeGame();
    bool hasWon(char symbol);
    bool isTie();
    GameState getState();
    void move(int position);

};