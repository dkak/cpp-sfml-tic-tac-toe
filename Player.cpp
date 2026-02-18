#include "Player.h"

Player::Player(char symbol) {
    this->symbol = symbol;
    this->wins = 0;
}

char Player::getSymbol() {
    return this->symbol;
}

int Player::getWins() {
    return this->wins;
}

void Player::move(char board[]) {}

void Player::incrementWins() {
    this->wins++;
}