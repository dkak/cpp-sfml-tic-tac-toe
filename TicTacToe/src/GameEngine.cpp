#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameEngine.h"
#include "Graphics.h"


GameEngine::GameEngine()
{
    this->graphics=new Graphics();
    this->game = new Game();
    this->transition_state= GameTransitionSequence::StartingMenu;
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
    if (transition_state ==GameTransitionSequence::StartingMenu || transition_state == GameTransitionSequence::Playing) return;

    transition_timer += dt;
    switch (transition_state) {
        case GameTransitionSequence::DrawingLine:
            if (transition_timer >= 1.0f) 
            {
                transition_state = GameTransitionSequence::ResultMessage;
                transition_timer = 0.0f;
            }
            break;
        case GameTransitionSequence::ResultMessage:
            if (transition_timer >= 1.0f) 
            {
                transition_state = GameTransitionSequence::FinalMenu;
                transition_timer = 0.0f;
            }
            break;
        default:
            break;
    }
}

void GameEngine::handleResize()
{
    // update view
    sf::View view(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(graphics->getWindow().getSize())));
    graphics->getWindow().setView(view);

    sf::Vector2f vSize = graphics->getWindow().getView().getSize();
    clickable_parts = graphics->calculateLayout(vSize.x, vSize.y);
}

void GameEngine::handleLeftMouseClick(sf::Vector2i mouse_position)
{  
    if (transition_state > GameTransitionSequence::Playing && transition_state < GameTransitionSequence::FinalMenu) return;

    // map the pixel to the current view coordinates
    sf::Vector2f world_pos = graphics->getWindow().mapPixelToCoords(mouse_position);

    switch (transition_state) {
        case GameTransitionSequence::StartingMenu:
            for (const auto& area : clickable_parts) {
                if (area.contains(world_pos.x, world_pos.y) && area.id == "single_player_button")
                {
                    game->initializeGame(GameType::Singleplayer);
                    transition_state = GameTransitionSequence::Playing;
                }
                else if (area.contains(world_pos.x, world_pos.y) && area.id == "multiplayer_button")
                {
                    game->initializeGame(GameType::Multiplayer);
                    transition_state = GameTransitionSequence::Playing;
                }
                else if (area.contains(world_pos.x, world_pos.y) && area.id == "exit_button")
                {
                    graphics->closeWindow();
                }
            }
            break;
        case GameTransitionSequence::Playing:
            userAction(world_pos);
            break;
        case GameTransitionSequence::FinalMenu:
            for (const auto& area : clickable_parts) {
                if (area.contains(world_pos.x, world_pos.y) && area.id == "play_again_button")
                {
                    game->restartGame();
                    transition_state = GameTransitionSequence::Playing;
                }
                else if (area.contains(world_pos.x, world_pos.y) && area.id == "main_menu_button")
                {
                    transition_state = GameTransitionSequence::StartingMenu;
                }
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
            graphics->closeWindow(); 
        }

        // when window is resized
        else if (event->is <sf::Event::Resized>()) 
        {
            handleResize();
        }

        else if(transition_state==GameTransitionSequence::Playing && game->getGameType()==GameType::Singleplayer && game->getSymbol()==Config::SYMBOL_O)
        {
            computerAction();
            if (game->getState() != GameState::Playing)
            {
                updateGameStats();
                transition_state = GameTransitionSequence::DrawingLine;
            }
        }

        // when user clicks left button
        else if (auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) 
        {
            if (mouse->button == sf::Mouse::Button::Left) 
            {
                handleLeftMouseClick(mouse->position);   
            }
        }
    }
}

void GameEngine::run() 
{    
    sf::Clock clock;
    
    // while window is still open
    while (graphics->getWindow().isOpen())
    {
        float dt = clock.restart().asSeconds();
        
        handleEvents();

        // handle the ui transitions
        updateTransition(dt);

        clickable_parts=graphics->render(game->getBoardArray(), game->getState(), transition_state, game->getGameStatistics(), game->getWinInfo());
    }
}

void GameEngine::userAction(sf::Vector2f world_pos)
{
    // get the current size of the view
    sf::Vector2f viewSize = graphics->getWindow().getView().getSize();

    float cell_w = viewSize.x / 3.0f;
    float cell_h = viewSize.y / 3.0f;

    int col = static_cast<int>(world_pos.x / cell_w);
    int row = static_cast<int>(world_pos.y / cell_h);
    if (col >= 0 && col < 3 && row >= 0 && row < 3)
    {
        int index = (row * 3) + col;
        game->move(index);
        if (game->getState() != GameState::Playing)
        {
            updateGameStats();
            transition_state = GameTransitionSequence::DrawingLine;
        }
    }
}

void GameEngine::computerAction()
{
    game->move();
}
