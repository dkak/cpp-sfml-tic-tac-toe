#pragma once
#include "Player.h"

class Human : public Player {
public:
    Human(char symbol);

    void move(char board[]) override;
};
