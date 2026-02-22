#include "Graphics.h"


#include <iostream>


Graphics::Graphics() : window(sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }), "Tic Tac Toe")
{}

sf::RenderWindow& Graphics::getWindow() {
	return this->window;
}

void Graphics::drawGrid(float space, float width, float position_x, float position_y)
{
	sf::RectangleShape line;
	line.setSize({ space * 3,width });
	line.setOrigin(line.getGeometricCenter());
	line.setFillColor(sf::Color(128, 128, 128));
	// horizontal
	line.setRotation(sf::degrees(0.f));
	line.setPosition({ position_x,position_y - space / 2 });
	window.draw(line);
	line.setPosition({ position_x,position_y + space / 2 });
	window.draw(line);
	// vertical
	line.setRotation(sf::degrees(90.f));
	line.setPosition({ position_x - space / 2 ,position_y });
	window.draw(line);
	line.setPosition({ position_x + space / 2 ,position_y });
	window.draw(line);
}

void Graphics::drawO(float size, float width, float position_x, float position_y)
{

	sf::CircleShape circle;
	circle.setRadius(size / 2);
	circle.setOrigin(circle.getGeometricCenter());
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(Config::O_COLOR);
	circle.setOutlineThickness(-width);
	circle.setPosition({ position_x,position_y });
	window.draw(circle);
}

void Graphics::drawX(float size, float width, float position_x, float position_y)
{
	sf::RectangleShape line;
	line.setSize({ size,width });
	line.setOrigin(line.getGeometricCenter());
	line.setFillColor(Config::X_COLOR);
	line.setPosition({ position_x,position_y });
	line.setRotation(sf::degrees(45.f));
	window.draw(line);
	line.setRotation(sf::degrees(-45.f));
	window.draw(line);
}

void Graphics::drawWinningLine(float size, float width,float position_x, float position_y, float angle, float scale,sf::Color outline_color)
{
	sf::RectangleShape line;
	line.setSize({ size * scale,width });
	line.setOrigin({ line.getGeometricCenter() });
	line.setFillColor(outline_color);
	line.setPosition({ position_x,position_y });
	line.setRotation(sf::degrees(angle));
	window.draw(line);
}

void Graphics::drawBoard(const char board[9],float size,float width) {
	// 1. Get current window dimensions
	float window_w = window.getView().getSize().x;
	float window_h = window.getView().getSize().y;

	// 2. Determine cell sizes
	float cell_w = window_w / 3.0f;
	float cell_h = window_h / 3.0f;

	for (int i = 0; i < 9; i++) {
		if (board[i] == ' ') continue; // Skip empty spots

		// Calculate Row and Column
		int row = i / 3;
		int col = i % 3;

		// Calculate the specific parameters for your functions
		float centerX = (col * cell_w) + (cell_w / 2.0f);
		float centerY = (row * cell_h) + (cell_h / 2.0f);

		if (board[i] == Config::SYMBOL_X) {
			drawX(size, width, centerX, centerY);
		}
		else if (board[i] == Config::SYMBOL_O) {
			drawO(size, width, centerX, centerY);
		}
	}
}

void Graphics::render(const char* board,GameState state)
{
	// size of window
	float window_w = window.getView().getSize().x;
	float window_h = window.getSize().y;
	float window_min = (window_w < window_h) ? window_w : window_h;

	// parameters
	float space = 0.3f * window_min; // size of space
	float size = 0.8f * space;		 // size of mark
	float width = 0.1f * size;		// line width

	// clear canvas before painting on it
	this->clear();

	// paint the grid
	this->drawGrid(space, width / 4, window_w / 2, window_h / 2);

	this->drawBoard(board,size,width);

	// game over scenarios
	switch (state) {
		case GameState::X_Wins:
		{
			//this->drawWinningLine(window_w / 2, window_h / 2, );
		}
		case GameState::O_Wins:
		{
			//this->drawWinningLine(window_w / 2, window_h / 2, );
		}
		case GameState::Draw:
		{
			// draw screen draw
		}
		default:
			break;


			// DrawWinningLine(space*3, width/2 , window_w/2, window_h/2, -45.f, 1.4f);
			// DrawWinningLine(space*3, width/2 , window_w/2, window_h/2, 45.f, 1.4f);

			// DrawWinningLine(space*3, width/2 , window_w/2, window_h/2+200.f*(i-1), 0.f);
			// DrawWinningLine(space*3, width/2 , window_w/2+200.f*(i-1), window_h/2, 90.f);
	}

	this->display();
}

void Graphics::display() {
	window.display();
}

void Graphics::clear() {
	window.clear(sf::Color::White);
}