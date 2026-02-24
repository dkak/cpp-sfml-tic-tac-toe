#include <iostream>

#include "Game.h"

Game::Game()
{
    this->initializeGame();
}

char* Game::getBoardArray()
{
    return board;
}

void Game::updateGameStats() 
{
    if (getState() == GameState::Playing) return;

    game_stats.total_games++;

    switch (getState()) {
        case GameState::X_Wins:
            game_stats.wins_x++;
            break;
        
        case GameState::O_Wins:
            game_stats.wins_o++;
            break;
        default:
            game_stats.draws++;
            break;
    }
}

void Game::initializeGame() {
    
    symbol = Config::SYMBOL_X;
    for (int i = 0; i < Config::BOARD_SIZE; i++) {
        this->board[i] = ' ';
    }

}

bool Game::hasWon(char symbol) {
    for (auto& comb : Config::WINNING_COMB) {
        if (this->board[comb[0]] == symbol && this->board[comb[1]]==symbol && this->board[comb[2]] == symbol) {
            win_info.positions[0] = comb[0];
            win_info.positions[1] = comb[1];
            win_info.positions[2] = comb[2];
            win_info.is_completed = true;
            return true;
        }
    }
    return false;
}

bool Game::isTie() 
{
    if (hasWon(Config::SYMBOL_X) || hasWon(Config::SYMBOL_O)) return false;
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

    /*
        do {
            srand(time(NULL));
            position = (rand() % 9);   // generate numbers between 0-8
        } while (board[position] != ' ');
        board[position] = this->getSymbol();
    */
}

GameStats Game::getGameStats() 
{
    return this->game_stats;
}

WinInfo Game::getWinInfo() {
    return win_info;
}