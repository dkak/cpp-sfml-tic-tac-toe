#include <iostream>

#include "Human.h"
#include "Player.h"

Human::Human(char symbol) : Player(symbol) {}

void Human::move(char board[]) {
    int position;
    int counter = 0;
    do {
        if (counter > 0) std::cout << "Spot already marked or invalid!\n";
        std::cout << "Player with symbol \"" << getSymbol() << "\" plays.\n";
        std::cout << "Enter a spot to place a marker (1-9): ";
        std::cin >> position;
        position--;     // to match arrays range [0-8]
        counter++;
    } while (position < 0 || position>8 || board[position] != ' ');

    board[position] = this->getSymbol();
}