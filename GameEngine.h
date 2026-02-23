#pragma once

#include "Graphics.h"
#include "Game.h"
#include "Types.h"

class GameEngine {
private:
    Graphics* graphics;
    Game* game_logic;
    Player* player_x;
    Player* player_o;
    EndingTransitionSequence transition_state;
    float transition_timer;

    void updateGameStats();
    void updateTransition(float dt);
    void handleEvents();
    
public:
    GameEngine(Player* player_x, Player* player_o);
    ~GameEngine();
    void run();
};

