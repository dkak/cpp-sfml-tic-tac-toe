#pragma once

#include "Graphics.h"
#include "Game.h"
#include "Types.h"

class GameEngine {
private:
    Graphics* graphics;
    Game* game;
    EndingTransitionSequence transition_state;
    float transition_timer;
    std::vector<Clickable> clickable_parts;

    void updateGameStats();
    void updateTransition(float dt);
    void handleEvents();
public:
    GameEngine();
    ~GameEngine();
    void run();
};

