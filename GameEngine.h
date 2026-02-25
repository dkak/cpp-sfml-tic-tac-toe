#pragma once

#include "Graphics.h"
#include "Game.h"
#include "Types.h"

class GameEngine {
private:
    Graphics* graphics;
    Game* game;
    GameTransitionSequence transition_state;
    float transition_timer;
    std::vector<Clickable> clickable_parts;

    void updateGameStats();
    void updateTransition(float dt);
    void handleResize();
    void handleLeftMouseClick(sf::Vector2i mouse_position, GameTransitionSequence transition_state);
    void handleEvents();
public:
    GameEngine();
    ~GameEngine();
    void run();
};

