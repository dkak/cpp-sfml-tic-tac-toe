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


	// while window is still open
    while (graphics->getWindow().isOpen() && this->running)
    {
        // handle events
        handleEvents();

        graphics->render(game_logic->getBoardArray());
    }
		
}

void GameEngine::handleEvents() {


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