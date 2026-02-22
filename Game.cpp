#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Graphics.h"


Game::Game()
{
    this->symbol = Config::SYMBOL_X;
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
    symbol = Config::SYMBOL_X;
}

void Game::initializeBoard() {
    for (int i = 0; i < Config::BOARD_SIZE; i++) {
        this->board[i] = ' ';
    }
}

bool Game::hasWon(char symbol) {
    for (auto& comb : Config::WINNING_COMB) {
        if (this->board[comb[0]] == symbol && this->board[comb[1]]==symbol && this->board[comb[2]] == symbol) {
            return true;
        }
    }
    return false;
}

bool Game::isTie() {
    for (int i = 0; i < Config::BOARD_SIZE; i++) {
        if (this->board[i] == ' ') return false;
    }
    return true;
}

GameState Game::getState() {
    if (isTie()) return GameState::Draw;
    else if (hasWon(Config::SYMBOL_X)) return GameState::X_Wins;
    else if (hasWon(Config::SYMBOL_O)) return GameState::O_Wins;
    else return GameState::Playing;
}

void Game::move(int position) 
{
    if (position >= 0 && position<=8 && board[position] == ' ') {
        board[position] = symbol;
        symbol = symbol == Config::SYMBOL_X ? Config::SYMBOL_O : Config::SYMBOL_X;
    }
}