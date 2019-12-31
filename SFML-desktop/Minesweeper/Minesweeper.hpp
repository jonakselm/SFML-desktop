#pragma once
#include "../State.hpp"
#include "../KeyHandler.hpp"
#include "../MouseHandler.hpp"
#include "MinesweeperBoard.hpp"

class Minesweeper :	public State
{
public:
	Minesweeper();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget& target);

private:
	KeyHandler m_keyHandler;
	MouseButtonHandler m_mouseHandler;
	MSBoard m_board;
};

