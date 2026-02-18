#pragma once

class Player {
private:
    char symbol;
    int wins;

public:
    Player(char symbol);

    char getSymbol();
    int getWins();
    void incrementWins();

    virtual void move(char board[]);
};