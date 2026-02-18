#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Graphics {
    private:
        static constexpr unsigned int WINDOW_WIDTH = 600;
        static constexpr unsigned int WINDOW_HEIGHT = 600;
        const char SYMBOL_X = 'X';
        const char SYMBOL_O = 'O';
        
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
        void drawWinningLine(float size, float width, float position_x, float position_y, float angle, float scale);
        void render(const char* board);
};
