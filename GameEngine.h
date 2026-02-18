#pragma once

#include "Graphics.h"
#include "Game.h"

class GameEngine {
private:
    Graphics* graphics;
    Game* game_logic;
    Player* player_x;
    Player* player_o;
    bool running;

    void handleEvents();
    void update();
public:
    GameEngine(Player* player_x, Player* player_o,bool running);
    ~GameEngine();
    void run();
};

