#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameEngine.h"
#include "Graphics.h"


GameEngine::GameEngine()
{
    this->graphics=new Graphics();
    this->game = new Game();
    this->transition_state= EndingTransitionSequence::None;
    transition_timer = 0.0f;
}

GameEngine::~GameEngine()
{
    delete this->graphics;
    this->graphics = nullptr;
    delete this->game;
    this->game = nullptr;
}

void GameEngine::updateGameStats()
{
    game->updateGameStats();
}

void GameEngine::updateTransition(float dt) 
{
    if (transition_state == EndingTransitionSequence::None) return;

    transition_timer += dt;
    switch (transition_state) {
        case EndingTransitionSequence::DrawingLine:
            if (transition_timer >= 0.5f) 
            {
                transition_state = EndingTransitionSequence::ShowingMessage;
                transition_timer = 0.0f;
            }
            break;
        case EndingTransitionSequence::ShowingMessage:
            if (transition_timer >= 1.0f) 
            {
                transition_state = EndingTransitionSequence::ShowingMenu;
                transition_timer = 0.0f;
            }
            break;
        default:
            break;
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
                        if (area.contains(worldPos.x, worldPos.y) && area.id == "play_again_button")
                        {
                            game->initializeGame();
                            transition_state = EndingTransitionSequence::None;
                        }
                        else if (area.contains(worldPos.x, worldPos.y) && area.id == "exit_button")
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
                if (col >= 0 && col < 3 && row >= 0 && row < 3) 
                {
                    int index = (row * 3) + col;
                    game->move(index);
                    if (game->getState() != GameState::Playing)
                    {
                        updateGameStats();
                        transition_state = EndingTransitionSequence::DrawingLine;
                    }
                }
            }
        }
    }
}

void GameEngine::run() {
    
    sf::Clock clock;
    
    // while window is still open
    while (graphics->getWindow().isOpen())
    {
        float dt = clock.restart().asSeconds();
        
        // handle events
        handleEvents();

        // handle the closing animation logic
        updateTransition(dt);

        clickable_parts=graphics->render(game->getBoardArray(), game->getState(), transition_state, game->getGameStatistics(), game->getWinInfo());
    }
}




