#pragma once
#include <iostream>

#include "Game.h"
#include "Types.h"

enum class GameType { Singleplayer, Multiplayer };

class Game {
private:
    char board[Config::BOARD_SIZE];
    char symbol;
    GameStatistics game_stats;
    WinInfo win_info;
    GameType game_type;
    
    void resetGameStats();
    bool isTie();
    bool hasWon(char symbol);
public:
    Game();
    char* getBoardArray();
    char getSymbol();
    GameStatistics getGameStatistics();
    GameState getState();
    WinInfo getWinInfo();
    GameType getGameType();
    
    void restartGame();
    void initializeGame(GameType game_type);
    void updateGameStats();
    void move();
    void move(int position);
};