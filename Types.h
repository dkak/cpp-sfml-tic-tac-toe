#pragma once

// 1. Enums
enum class GameState { Playing, X_Wins, O_Wins, Draw };
enum class EndSequence { None, DrawingLine, ShowingMessage, ShowingMenu };

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