#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Types.h"

class Graphics {
    private:
        sf::RenderWindow window;
        sf::Font graphics_font;
        std::vector<Clickable> clickable_parts;

        void clear();
        void display();
        void drawGrid(float space, float width, float position_x, float position_y);
        void drawX(float size, float width, float position_x, float position_y);
        void drawO(float size, float width, float position_x, float position_y);
        void drawBoard(const char* board, float size, float width);
        void drawWinningLine(float size, float width, float position_x, float position_y, float angle, float scale, GameState game_state);
        void drawMessage(GameState game_state);
        void drawMenu(float window_w, float window_h, GameStatistics game_stats);
        Clickable drawButton(std::string label, sf::Vector2f position, sf::Color color, std::string clickable_id);
    public:
        Graphics();
        sf::RenderWindow& getWindow();
        
        std::vector<Clickable> render(const char* board, GameState state, EndingTransitionSequence transition_state, GameStatistics game_stats, WinInfo win_info);
};
