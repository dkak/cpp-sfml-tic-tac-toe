#pragma once
#include <string>

// 1. Enums
enum class GameState { Playing, X_Wins, O_Wins, Draw };
enum class EndingTransitionSequence { None, DrawingLine, ShowingMessage, ShowingMenu };


struct WinInfo {
    bool is_completed = false;
    int positions[3];
};

struct GameStats{
    int wins_x = 0;
    int wins_o = 0;
    int draws = 0;
    int total_games = 0;
};

struct Clickable {
    std::string id;
    float x, y, width, height;

    bool contains(float mouseX, float mouseY) const {
        // 1. Calculate the Top-Left corner (because Rects start there)
        sf::Vector2f topLeft(x - (width / 2.0f), y - (height / 2.0f));

        // 2. Define the Size
        sf::Vector2f size(width, height);

        // 3. Create the Rect (In SFML 3, this takes two vectors)
        sf::FloatRect bounds(topLeft, size);

        // 4. Perform the check
        return bounds.contains({ mouseX, mouseY });
    }
};

// 2. Constants
namespace Config {

    // Board dimensions
    const int BOARD_SIZE = 9;
    const char SYMBOL_X = 'X';
    const char SYMBOL_O = 'O';
    const int WINNING_COMB[8][3] = {
                            {0,1,2},{0,3,6},{0,4,8},
                            {1,4,7},{2,4,6},{2,5,8},
                            {3,4,5},{6,7,8}
    };

    // Symbols colors
    const sf::Color X_COLOR = sf::Color(170, 255, 0);
    const sf::Color O_COLOR = sf::Color(0, 170, 255);

    // window dimensions
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 600;

}