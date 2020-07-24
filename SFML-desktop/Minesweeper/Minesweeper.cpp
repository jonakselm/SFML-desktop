#include "stdafx.h"
#include "Minesweeper.hpp"
#include "../StateHandler.hpp"

Minesweeper::Minesweeper(sf::Vector2i boardSize, int nBombs)
	:
	m_boardSize(boardSize),
	m_nBombs(nBombs),
	m_board(boardSize, nBombs)
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
			stateHandler.Switch<Minesweeper>(m_boardSize, m_nBombs);
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

			m_won = m_board.checkForWin();
		});

	m_font.loadFromFile("data/fonts/Georgia.ttf");

	m_winText.setFont(m_font);
	m_gameOverText.setFont(m_font);

	m_winText.setString("You win");
	m_gameOverText.setString("Game Over");

	m_winText.setOutlineThickness(1);
	m_gameOverText.setOutlineThickness(1);

	m_winText.setOutlineColor(sf::Color::Black);
	m_gameOverText.setOutlineColor(sf::Color::Black);

	sf::Vector2f boardCenter = sf::Vector2f((m_board.getCellDim() * m_boardSize.x / 2) - m_board.getCellDim() * 2, (m_board.getCellDim() * m_boardSize.y / 2) - m_board.getCellDim() / 2);

	m_winText.setPosition(boardCenter);
	m_gameOverText.setPosition(boardCenter);

	m_winText.setCharacterSize((unsigned)m_board.getCellDim());
	m_gameOverText.setCharacterSize((unsigned)m_board.getCellDim());
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

	if (m_board.isGameWon())
		target.draw(m_winText);
	if (m_board.isGameOver())
		target.draw(m_gameOverText);
}
