#pragma once
#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Graphics.h"
#include "Types.h"

class Game {
private:
    int games_played;
    char board[Config::BOARD_SIZE];
    char symbol;

    int getGamesPlayed();
public:
    Game();
    char* getBoardArray();
    void incrementGamesPlayed();
    void initializeGame();
    void initializeBoard();
    bool hasWon(char symbol);
    bool isTie();
    GameState getState();
    void move(int position);

};