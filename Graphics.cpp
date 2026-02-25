#include "Graphics.h"


#include <iostream>
#include <string>
#include <cmath>

Graphics::Graphics()
	: window(sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }), "Tic Tac Toe")
{	 
	if (!graphics_font.openFromFile("arial.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}
}

sf::RenderWindow& Graphics::getWindow() 
{
	return this->window;
}

void Graphics::display() 
{
	window.display();
}

void Graphics::clear() 
{
	window.clear(sf::Color::White);
}

void Graphics::closeWindow()
{
	window.close();
}

std::vector<Clickable> Graphics::calculateLayout(float window_w, float window_h)
{
	std::vector<Clickable> current_clicks;

	float centerX = window_w * 0.5f;
	float startY = window_h * 0.4f;
	float spacing = 80.0f;
	float btnW = 180.0f;
	float btnH = 60.0f;

	// Single-Player
	current_clicks.push_back({ "single_player_button", centerX - (btnW / 2.0f), startY - (btnH / 2.0f), btnW, btnH });

	// Multi-Player
	current_clicks.push_back({ "multiplayer_button", centerX - (btnW / 2.0f), (startY + spacing) - (btnH / 2.0f), btnW, btnH });

	// Exit
	current_clicks.push_back({ "exit_button", centerX - (btnW / 2.0f), (startY + 2 * spacing) - (btnH / 2.0f), btnW, btnH });

	return current_clicks;
}

void Graphics::drawGrid(float space, float width, float position_x, float position_y)
{	
	// create the lines
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

void Graphics::drawBoard(const char board[9], float size, float width) 
{	
	// current window dimensions
	float window_w = window.getView().getSize().x;
	float window_h = window.getView().getSize().y;

	// determine cell sizes
	float cell_w = window_w / 3.0f;
	float cell_h = window_h / 3.0f;

	for (int i = 0; i < 9; i++) 
	{
		if (board[i] == ' ') continue; // Skip empty spots

		// calculate row and column
		int row = i / 3;
		int col = i % 3;

		// calculate the specific parameters
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

void Graphics::drawWinningLine(float size, float width,float position_x, float position_y, float angle, float scale, GameState game_state)
{
	if (game_state == GameState::Draw) return;

	sf::Color outline_color;
	if (game_state == GameState::X_Wins) outline_color = Config::X_COLOR;
	else if (game_state == GameState::O_Wins) outline_color = Config::O_COLOR;
	else return;

	sf::RectangleShape line;
	line.setSize({ size * scale,width });
	line.setOrigin({ line.getGeometricCenter() });
	line.setFillColor(outline_color);
	line.setPosition({ position_x,position_y });
	line.setRotation(sf::degrees(angle));
	window.draw(line);
}

void Graphics::drawMessage(GameState game_state)
{
	// draw the dark overlay
	sf::RectangleShape overlay;
	overlay.setSize(sf::Vector2f(window.getSize()));
	overlay.setPosition({ 0, 0 });
	overlay.setFillColor(sf::Color(0, 0, 0, 210));
	window.draw(overlay);

	// create the result's message
	sf::Text graphics_text(graphics_font);
	graphics_text.setCharacterSize(80);
	graphics_text.setFillColor(sf::Color::Yellow);
	if (game_state == GameState::X_Wins)
	{
		graphics_text.setString("X WINS!");
		graphics_text.setFillColor(Config::X_COLOR);
	}
	else if (game_state == GameState::O_Wins)
	{
		graphics_text.setString("O WINS!");
		graphics_text.setFillColor(Config::O_COLOR);
	}
	else graphics_text.setString("DRAW!");

	// center and draw
	sf::FloatRect bounds = graphics_text.getLocalBounds();
	graphics_text.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
	graphics_text.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });

	window.draw(graphics_text);
}

void Graphics::drawStartingMenu(float window_w, float window_h, GameStatistics game_stats)
{
	// draw the dark dverlay
	sf::RectangleShape overlay;
	overlay.setSize(sf::Vector2f(window.getSize()));
	overlay.setPosition({ 0, 0 });
	overlay.setFillColor(sf::Color(0, 0, 0, 250));
	window.draw(overlay);

	// draw the stats
	sf::Text welcome_text(graphics_font);
	
	std::string string_message = " Welcome! ";
	welcome_text.setString(string_message);
	welcome_text.setCharacterSize(40);
	welcome_text.setFillColor(Config::X_COLOR);

	// calculate positioning of the stats
	sf::FloatRect bounds = welcome_text.getLocalBounds();
	welcome_text.setOrigin({
		bounds.position.x + (bounds.size.x / 2.0f),
		bounds.position.y + (bounds.size.y / 2.0f)
		});
	welcome_text.setPosition({ window_w / 2.0f, window_h * 0.1f });

	window.draw(welcome_text);

	float spacing = 80.0f;

	// draw the buttons
	clickable_parts.push_back(drawButton("Single-Player", { window_w * 0.5f, window_h * 0.4f }, sf::Color::Green, "single_player_button"));
	clickable_parts.push_back(drawButton("Multi-Player", { window_w * 0.5f, window_h*0.4f +spacing }, sf::Color::Blue, "multiplayer_button"));
	clickable_parts.push_back(drawButton("Exit", { window_w * 0.5f, window_h * 0.4f + 2 * spacing }, sf::Color::Red, "exit_button"));
}

void Graphics::drawFinalMenu(float window_w,float window_h, GameStatistics game_stats)
{
	// draw the dark dverlay
	sf::RectangleShape overlay;
	overlay.setSize(sf::Vector2f(window.getSize()));
	overlay.setPosition({ 0, 0 });
	overlay.setFillColor(sf::Color(0, 0, 0, 250));
	window.draw(overlay);

	// draw the stats
	sf::Text text_stats_x(graphics_font);
	sf::Text text_stats_o(graphics_font);
	sf::Text text_stats_draws(graphics_font);

	std::string string_stats_x = " X : " + std::to_string(game_stats.wins_x);
	std::string string_stats_o = " O : " + std::to_string(game_stats.wins_o);
	std::string string_stats_draws = " Draws : " + std::to_string(game_stats.draws);

	text_stats_x.setString(string_stats_x);
	text_stats_o.setString(string_stats_o);
	text_stats_draws.setString(string_stats_draws);

	text_stats_x.setCharacterSize(40);
	text_stats_o.setCharacterSize(40);
	text_stats_draws.setCharacterSize(40);

	text_stats_x.setFillColor(Config::X_COLOR);
	text_stats_o.setFillColor(Config::O_COLOR);
	text_stats_draws.setFillColor(sf::Color::White);
	
	// calculate positioning of the stats
	sf::FloatRect bounds = text_stats_x.getLocalBounds();
	text_stats_x.setOrigin({
		bounds.position.x + (bounds.size.x / 2.0f),
		bounds.position.y + (bounds.size.y / 2.0f)
		});
	text_stats_x.setPosition({ window_w / 3.0f, window_h * 0.1f });

	bounds = text_stats_o.getLocalBounds();
	text_stats_o.setOrigin({
		bounds.position.x + (bounds.size.x / 2.0f),
		bounds.position.y + (bounds.size.y / 2.0f)
		});
	text_stats_o.setPosition({ window_w / 3.0f*2, window_h * 0.1f });

	bounds = text_stats_draws.getLocalBounds();
	text_stats_draws.setOrigin({
		bounds.position.x + (bounds.size.x / 2.0f),
		bounds.position.y + (bounds.size.y / 2.0f)
		});
	text_stats_draws.setPosition({ window_w / 2.0f, window_h * 0.2f });

	window.draw(text_stats_x);
	window.draw(text_stats_o);
	window.draw(text_stats_draws);

	// draw the buttons
	clickable_parts.push_back(drawButton("PLAY AGAIN", { window_w * 0.35f, window_h * 0.6f }, sf::Color::Green,"play_again_button"));
	clickable_parts.push_back(drawButton("EXIT", { window_w * 0.65f, window_h * 0.6f }, sf::Color::Red,"exit_button"));

}

Clickable Graphics::drawButton(std::string label, sf::Vector2f position, sf::Color color,std::string clickable_id) 
{
	float btnWidth = 180.0f;
	float btnHeight = 60.0f;

	// button's box
	sf::RectangleShape box({ btnWidth, btnHeight });
	box.setFillColor(color);
	box.setOutlineThickness(3);
	box.setOutlineColor(sf::Color::White);
	box.setOrigin({ btnWidth / 2.0f, btnHeight / 2.0f });
	box.setPosition(position);
	window.draw(box);

	// button's label
	sf::Text statusText(graphics_font);
	statusText.setString(label);
	statusText.setCharacterSize(20);
	statusText.setFillColor(sf::Color::White);
	statusText.setStyle(sf::Text::Style::Bold);

	// label positioning
	auto bounds = statusText.getLocalBounds();
	statusText.setOrigin({ bounds.position.x + bounds.size.x / 2.0f,
							bounds.position.y + bounds.size.y / 2.0f });
	statusText.setPosition(position);
	window.draw(statusText);

	return { clickable_id, position.x, position.y, btnWidth, btnHeight };
}

std::vector<Clickable> Graphics::render(const char* board, GameState game_state, GameTransitionSequence transition_state, GameStatistics game_stats,WinInfo win_info)
{
	// size of window
	float window_w = window.getView().getSize().x;
	float window_h = window.getSize().y;
	float window_min = (window_w < window_h) ? window_w : window_h;

	// parameters
	float space = 0.3f * window_min;
	float size = 0.8f * space;
	float width = 0.1f * size;

	// clear canvas before painting on it
	this->clear();

	sf::Vector2f vSize = getWindow().getView().getSize();
	// Get the layout
	clickable_parts = calculateLayout(vSize.x, vSize.y);
	
	// game animations
	switch (transition_state) {
		case GameTransitionSequence::StartingMenu:
		{
			drawStartingMenu(window_w, window_h, game_stats);
			break;
		}
		case GameTransitionSequence::Playing:
		{
			drawGrid(space, width / 4, window_w / 2, window_h / 2);
			drawBoard(board, size, width);
			break;
		}
		case GameTransitionSequence::DrawingLine:
		{
			drawGrid(space, width / 4, window_w / 2, window_h / 2);
			drawBoard(board, size, width);

			if (win_info.positions[0] + 2 == win_info.positions[2]) // Horizontal
			{

				drawWinningLine(space * 3, width / 2, window_w / 2, window_h / 2 + 200.f * (win_info.positions[0]/3 - 1 ), 0.f, 1.f,game_state);
			}
			else if(win_info.positions[0] + 6 == win_info.positions[2]) // Vertical
			{
				drawWinningLine(space * 3, width / 2, window_w / 2 + 200.f * (win_info.positions[0] % 3 - 1), window_h / 2, 90.f,1.f, game_state);
			}
			else if(win_info.positions[0] + 8 == win_info.positions[2]) // Diagonal 1
			{
					drawWinningLine(space*3, width/2 , window_w/2, window_h/2, 45.f, 1.4f, game_state);
			}
			else // Diagonal 2
			{
				drawWinningLine(space * 3, width / 2, window_w / 2, window_h / 2, -45.f, 1.4f, game_state);
			}
			break;
		}
		case GameTransitionSequence::ResultMessage:
		{
			drawGrid(space, width / 4, window_w / 2, window_h / 2);
			drawBoard(board, size, width);
			drawMessage(game_state);
			break;
		}
		case GameTransitionSequence::FinalMenu:
		{
			drawFinalMenu(window_w, window_h, game_stats);
			break;
		}
		default:
			break;
	}
	
	display();

	return clickable_parts;
}