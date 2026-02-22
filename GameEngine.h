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
    bool running;

    // Not sure
    EndSequence endStage = EndSequence::None;
    float timer = 0.0f;
    float lineProgress = 0.0f;

    void handleEvents();
    void update();
    void updateGameStats(GameState state);
    void updateEndSequence(float dt, GameState state);
public:
    GameEngine(Player* player_x, Player* player_o,bool running);
    ~GameEngine();
    void run();
};

