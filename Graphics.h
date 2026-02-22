#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Types.h"

class Graphics {
    private:
        sf::RenderWindow window;
    public:
        Graphics();

        sf::RenderWindow& getWindow();

        void clear();
        void display();
        void drawGrid(float space, float width, float position_x, float position_y);
        void drawX(float size, float width, float position_x, float position_y);
        void drawO(float size, float width, float position_x, float position_y);
        void drawBoard(const char* board, float size, float width);
        void drawWinningLine(float size, float width, float position_x, float position_y, float angle, float scale, sf::Color outline_color);
        void render(const char* board,GameState state);
};
