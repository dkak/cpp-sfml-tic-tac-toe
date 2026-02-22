#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameEngine.h"
#include "Human.h"
#include "Computer.h"
#include "Graphics.h"


GameEngine::GameEngine(Player* player_x, Player* player_o,bool running)
{
    this->player_x = player_x;
    this->player_o = player_o;
    this->running = running;
    this->graphics=new Graphics();
    this->game_logic = new Game();
}

GameEngine::~GameEngine()
{
    delete this->player_x;
    this->player_x = nullptr;
    delete this->player_o;
    this->player_o = nullptr;
    delete this->graphics;
    this->graphics = nullptr;
    delete this->game_logic;
    this->game_logic = nullptr;
}

void GameEngine::run() {
    
    sf::Clock clock;
    bool stats_updated = false;
    
    // while window is still open
    while (graphics->getWindow().isOpen() && this->running)
    {
        float dt = clock.restart().asSeconds();
        
        // handle events
        handleEvents();

        // handle the animation logic
        update(dt);

        graphics->render(game_logic->getBoardArray(), game_logic->getState());
        
        //if (game_logic->getState() != GameState::Playing && !stats_updated) 
        //{
        //    updateGameStats(game_logic->getState());
        //    stats_updated = true;
        //}
    }
}

void GameEngine::handleEvents()
{
    while (std::optional event = graphics->getWindow().pollEvent())
    {

        // when close button is clicked
        if (event->is<sf::Event::Closed>())
        {
            // close window
            graphics->getWindow().close();
            this->running = false;
        }

        // when window is resized
        else if (event->is <sf::Event::Resized>())
        {
            // update view
            sf::View view(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(graphics->getWindow().getSize())));
            graphics->getWindow().setView(view);
        }

        // when game is over wait for user's choice
        else if (game_logic->getState() != GameState::Playing) {
            if (auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    // Process move logic here...
                    // processMove(mouse->position);
                    std::cout << "Game Over";
                }
            }
        }

        // when mouse button is pressed
        else if (auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouse->button == sf::Mouse::Button::Left)
            {
                // Get the FRESH size of the view right now
                sf::Vector2f viewSize = graphics->getWindow().getView().getSize();

                float cell_w = viewSize.x / 3.0f;
                float cell_h = viewSize.y / 3.0f;

                // Map the pixel to the current view coordinates
                sf::Vector2f worldPos = graphics->getWindow().mapPixelToCoords(mouse->position);


                int col = static_cast<int>(worldPos.x / cell_w);
                int row = static_cast<int>(worldPos.y / cell_h);
                if (col >= 0 && col < 3 && row >= 0 && row < 3) {
                    int index = (row * 3) + col;
                    game_logic->move(index);
                }

            }
        }
    }
}

void GameEngine::updateGameStats(GameState state) 
{
    game_logic->incrementGamesPlayed();
    switch (state) {
        case GameState::X_Wins:
        {
            player_x->incrementWins();
        }
        case GameState::O_Wins:
        {
            player_o->incrementWins();
        }
        default:
            break;
    }
}

void GameEngine::updateEndSequence(float dt, GameState state) {
    if (endStage == EndSequence::None) endStage = EndSequence::DrawingLine;

    switch (endStage) {
        case EndSequence::DrawingLine:
            lineProgress += dt * 2.0f;
            if (lineProgress >= 1.0f) {
                lineProgress = 1.0f;
                timer += dt;
                if (timer > 0.5f) { endStage = EndSequence::ShowingMessage; timer = 0.0f; }
            }
            break;
        case EndSequence::ShowingMessage:
            timer += dt;
            if (timer > 1.5f) endStage = EndSequence::ShowingMenu;
            break;
    }
}