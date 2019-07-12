#include "stdafx.h"
#include "SnakeGame.hpp"
#include "StateHandler.hpp"
#include <sstream>
#include "SFML-ext.hpp"

SnakeGame::SnakeGame(int nColors, sf::Color startColor, Snake::ColorInit colorInit, int increment)
	:
	nColors(nColors),
	startColor(startColor),
	colorInit(colorInit),
	increment(increment),
	m_snake({ 1,1 }, nColors, startColor, colorInit, increment),
	m_snakeBot(m_board.getSize() - sf::Vector2f(2, 2), nColors, startColor, colorInit, increment),
	m_apple(m_snake, m_snakeBot)
{
}


SnakeGame::~SnakeGame()
{
}

void SnakeGame::init(sf::Window & window, StateHandler & stateHandler)
{
	auto &kEsc = m_keyHandler.addKey(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});

	font.loadFromFile("data/fonts/Georgia.ttf");
	buttonHandler.setDefaultSize(200, 100);
	buttonHandler.setFont(font);
	buttonHandler.setNextPosition(450, 400);

	auto &bRestart = buttonHandler.addButton("Game Over!\nRestart?", [&]
		{
			stateHandler.Switch<SnakeGame>(nColors, startColor, colorInit, increment);
		});

	userScore.setFont(font);
	userScore.setPosition(10, 5);

	botScore.setFont(font);
	botScore.setPosition(940, 5);
}

void SnakeGame::updateModel(sf::Window &window, StateHandler &stateHandler)
{
	std::string snakeScore = std::to_string(m_snake.getScore());
	userScore.setString(snakeScore);

	std::string botSnakeScore = std::to_string(m_snakeBot.getScore());
	botScore.setString(botSnakeScore);

	float dt = ft.Mark();
	if (!gameOver || !m_snakeBot.isDead())
	{
		snakeMoveCounter += dt;

		if (snakeMoveCounter >= snakeMovePeriod)
		{
			snakeMoveCounter -= snakeMovePeriod;
			const sf::Vector2f next = m_snake.getNextLoc(delta_loc);

			if (m_snake.inTileExceptEnd(next) ||
				!m_board.insideBoard(next))
			gameOver = true;

			if (m_apple.getGlobalBounds().intersects(m_snake.getNextBounds(delta_loc)))
			{
				m_snake.growAndMoveBy(delta_loc);
				m_apple.respawn(m_snake, m_snakeBot);
			}
			else
			{
				m_snake.moveBy(delta_loc);
			}

			if (!m_snakeBot.isDead())
			{
				if (m_apple.getGlobalBounds().intersects(m_snakeBot.getNextBounds(m_snake, m_apple)))
				{
					m_snakeBot.growAndMoveBy(m_snake, m_apple);
					m_apple.respawn(m_snake, m_snakeBot);
				}
				else
				{
					m_snakeBot.update(m_snake, m_apple);
				}
			}
		}

		snakeMovePeriod = std::max(snakeMovePeriod - dt * snakeSpeedupFactor, snakeMovePeriodMin);
	}
}

void SnakeGame::handleExtraEvents(sf::Window &window, StateHandler &stateHandler)
{
	if (sf::Joystick::isButtonPressed(0, sfExt::Joystick::Circle))
		stateHandler.Pop();

	m_keyHandler.handleKeyInput();
	if (gameOver)
		buttonHandler.handleInput(window);

	if (!gameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Joystick::isButtonPressed(0, sfExt::Joystick::Up))
		{
			const sf::Vector2f new_delta_loc = { 0,-1 };
			if (delta_loc != -new_delta_loc || m_snake.getLength() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Joystick::isButtonPressed(0, sfExt::Joystick::Down))
		{
			const sf::Vector2f new_delta_loc = { 0,1 };
			if (delta_loc != -new_delta_loc || m_snake.getLength() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Joystick::isButtonPressed(0, sfExt::Joystick::Left))
		{
			const sf::Vector2f new_delta_loc = { -1,0 };
			if (delta_loc != -new_delta_loc || m_snake.getLength() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Joystick::isButtonPressed(0, sfExt::Joystick::Right))
		{
			const sf::Vector2f new_delta_loc = { 1,0 };
			if (delta_loc != -new_delta_loc || m_snake.getLength() <= 2)
				delta_loc = new_delta_loc;
		}
	}
}

void SnakeGame::draw(sf::RenderTarget & target) const
{
	if (!gameOver || !m_snakeBot.isDead())
	{
		m_board.drawBoard(target);
		m_apple.draw(target);
	}
	else if (gameOver && m_snakeBot.isDead())
	{
		buttonHandler.draw(target);
	}
	if (!m_snakeBot.isDead())
	{
		m_snakeBot.draw(target);
	}
	if (!gameOver)
	{
		m_snake.draw(target);
	}

	target.draw(userScore);
	target.draw(botScore);
}
