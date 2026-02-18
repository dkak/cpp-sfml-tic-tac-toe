#pragma once
#include "Player.h"

class Computer : public Player {
public:
    Computer(char symbol);

    void move(char board[]) override;
};

