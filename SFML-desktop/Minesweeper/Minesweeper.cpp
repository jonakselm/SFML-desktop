#include "stdafx.h"
#include "Minesweeper.hpp"
#include "../StateHandler.hpp"

Minesweeper::Minesweeper()
	:
	m_board(sf::Vector2i(10, 10), 40)
{
}

void Minesweeper::init(sf::Window & window, StateHandler & stateHandler)
{
	m_keyHandler.onKeyPressed(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});
	m_keyHandler.onKeyPressed(sf::Keyboard::R, [&]
		{
			stateHandler.Switch<Minesweeper>();
		});

	m_mouseHandler.onButtonPressed(sf::Mouse::Left, [&](MouseButtonEvent e)
		{
			auto pos = sf::Mouse::getPosition(window);
			m_board.onLeftClick(pos.x, pos.y);
		});

	m_mouseHandler.onButtonPressed(sf::Mouse::Right, [&](MouseButtonEvent e)
		{
			auto pos = sf::Mouse::getPosition(window);
			m_board.onRightClick(pos.x, pos.y);
		});
}

void Minesweeper::updateModel(sf::Window & window, StateHandler & stateHandler)
{
}

void Minesweeper::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	m_keyHandler.handleKeyInput();
	m_mouseHandler.handleButtonInput();
}

void Minesweeper::draw(sf::RenderTarget & target)
{
	m_board.draw(target);
}
