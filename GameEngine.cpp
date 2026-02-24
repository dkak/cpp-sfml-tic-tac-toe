#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameEngine.h"
#include "Human.h"
#include "Computer.h"
#include "Graphics.h"


GameEngine::GameEngine(Player* player_x, Player* player_o)
{
    this->player_x = player_x;
    this->player_o = player_o;
    this->graphics=new Graphics();
    this->game_logic = new Game();
    this->transition_state= EndingTransitionSequence::None;
    transition_timer = 0.0f;

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

void GameEngine::updateGameStats()
{
    game_logic->updateGameStats();
}

void GameEngine::updateTransition(float dt) {

    if (transition_state == EndingTransitionSequence::None) return;

    transition_timer += dt;
    switch (transition_state) {
        case EndingTransitionSequence::DrawingLine:
            if (transition_timer >= 0.5f) {
                transition_state = EndingTransitionSequence::ShowingMessage;
                transition_timer = 0.0f;
            }
            break;
        case EndingTransitionSequence::ShowingMessage:
            if (transition_timer >= 1.0f) {
                transition_state = EndingTransitionSequence::ShowingMenu;
                transition_timer = 0.0f;
            }
            break;
        default:
            break;
    }
}

void GameEngine::run() {
    
    sf::Clock clock;
    bool stats_updated = false;
    
    // while window is still open
    while (graphics->getWindow().isOpen())
    {
        float dt = clock.restart().asSeconds();
        
        // handle events
        handleEvents();

        // handle the closing animation logic
        updateTransition(dt);

        clickable_parts=graphics->render(game_logic->getBoardArray(), game_logic->getState(), transition_state, transition_timer,game_logic->getGameStats(),game_logic->getWinInfo());
        
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
        }

        // when window is resized
        else if (event->is <sf::Event::Resized>())
        {
            // update view
            sf::View view(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(graphics->getWindow().getSize())));
            graphics->getWindow().setView(view);
        }

        // when the game is over wait for the transition
        else if (transition_state > EndingTransitionSequence::None && transition_state < EndingTransitionSequence::ShowingMenu) {}

        // when user selects between "Play Again" and "Exit"
        else if (transition_state == EndingTransitionSequence::ShowingMenu) {
            if (auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {

                    sf::Vector2f worldPos = graphics->getWindow().mapPixelToCoords(mouse->position);

                    for (const auto& area : clickable_parts) {
                        if (area.contains(worldPos.x, worldPos.y) && area.id=="play_again_button") 
                        {
                            game_logic->initializeGame();
                            transition_state = EndingTransitionSequence::None;
                        }
                        else if(area.contains(worldPos.x, worldPos.y) && area.id == "exit_button")
                        {
                            graphics->getWindow().close();
                        }
                    }
                }
            }
        }

        // when user plays
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
                    if (game_logic->getState() != GameState::Playing)
                    {
                        updateGameStats();
                        transition_state = EndingTransitionSequence::DrawingLine;
                    }
                }
            }
        }
    }
}



