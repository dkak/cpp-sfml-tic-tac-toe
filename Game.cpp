#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Graphics.h"

Game::Game()
{
    this->next_symbol = SYMBOL_X;
    this->initializeBoard();
    this->games_played = 0;
}

int Game::getGamesPlayed() {
    return this->games_played;
}

char* Game::getBoardArray()
{
    return board;
}

void Game::incrementGamesPlayed() {
    games_played++;
}

void Game::initializeGame() {
    games_played = 0;
    next_symbol = SYMBOL_X;
}

void Game::initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        this->board[i] = ' ';
    }
}

bool Game::checkWin() {
    for (auto& comb : WINNING_COMB) {
        if (this->board[comb[0]] == this->board[comb[1]] && this->board[comb[1]] == this->board[comb[2]]) {
            return true;
        }
    }
    return false;
}

bool Game::checkTie() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (this->board[i] == ' ') return false;
    }
    return true;
}

bool Game::checkCompletion() {
    if (checkWin() || checkTie()) {
        this->incrementGamesPlayed();
        this->initializeBoard();
        return true;
    }
    return false;
}

bool Game::move(int position) 
{
    if (position < 0 || position>8 || board[position] != ' ')
    {
        return false;
    }
    board[position] = next_symbol;
    next_symbol == SYMBOL_X ? SYMBOL_O : SYMBOL_X;
    return true;
}