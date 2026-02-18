#include <iostream>

#include "GameEngine.h"
#include "Player.h"

int main() {

    Player* p1 = new Human('X');
    Player* p2 = new Computer('O');

    GameEngine game_engine(p1, p2,true);

    game_engine.run();

    return 0;
}