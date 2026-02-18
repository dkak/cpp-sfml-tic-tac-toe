#include <iostream>

#include "Computer.h"
#include "Player.h"

Computer::Computer(char symbol) :Player(symbol) {}

void Computer::move(char board[]) {
    int position;
    std::cout << "Computer with symbol \"" << getSymbol() << "\" plays.\n";
    do {
        srand(time(NULL));
        position = (rand() % 9);   // generate numbers between 0-8
    } while (board[position] != ' ');
    board[position] = this->getSymbol();
}