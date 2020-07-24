#pragma once
#include "../State.hpp"
#include "../KeyHandler.hpp"
#include "../MouseHandler.hpp"
#include "../ButtonHandler.hpp"
#include "MinesweeperBoard.hpp"

class Minesweeper :	public State
{
public:
	Minesweeper(sf::Vector2i boardSize, int nBombs);

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget& target);

private:
	ButtonHandler m_buttonHandler;
	KeyHandler m_keyHandler;
	MouseButtonHandler m_mouseHandler;
	MSBoard m_board;
	sf::Font m_font;
	sf::Text m_winText, m_gameOverText;

	bool m_gameOver = false;
	bool m_won = false;

	const sf::Vector2i m_boardSize;
	const int m_nBombs;
};

