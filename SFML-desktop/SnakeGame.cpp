#include "stdafx.h"
#include "SnakeGame.hpp"
#include "StateHandler.hpp"
#include <sstream>
#include "SFML-ext.hpp"

SnakeGame::SnakeGame(int nColors, sf::Color startColor, ColorInit colorInit, int increment)
	:
	lastTime(0),
	nColors(nColors),
	startColor(startColor),
	colorInit(colorInit),
	increment(increment),
	m_snake({ 1,1 }, nColors, startColor, colorInit, increment)
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

	score.setFont(font);
	score.setPosition(10, 5);
}

void SnakeGame::updateModel(sf::Window &window, StateHandler &stateHandler)
{
	std::string snakeScore = std::to_string(m_snake.getScore());
	score.setString(snakeScore);

	float dt = ft.Mark();
	if (!gameOver)
	{
		snakeMoveCounter += dt;
		int64_t time = 200'000;
		if (snakeMoveCounter >= (snakeMovePeriod + lastTime))
		{
			lastTime += (int64_t)dt;
			snakeMoveCounter -= snakeMovePeriod;
			const sf::Vector2f next = m_snake.nextHeadLoc(delta_loc);

			if (m_snake.inTileExceptEnd(next) ||
				!board.InsideBoard(next))
			gameOver = true;

			if (m_apple.getGlobalBounds().intersects(m_snake.getNextBounds(delta_loc)))
			{
				m_snake.growAndMoveBy(delta_loc);
				m_apple.respawn();

			}
			else
			{
				m_snake.moveBy(delta_loc);
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
			if (delta_loc != -new_delta_loc || m_snake.getLenght() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Joystick::isButtonPressed(0, sfExt::Joystick::Down))
		{
			const sf::Vector2f new_delta_loc = { 0,1 };
			if (delta_loc != -new_delta_loc || m_snake.getLenght() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Joystick::isButtonPressed(0, sfExt::Joystick::Left))
		{
			const sf::Vector2f new_delta_loc = { -1,0 };
			if (delta_loc != -new_delta_loc || m_snake.getLenght() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Joystick::isButtonPressed(0, sfExt::Joystick::Right))
		{
			const sf::Vector2f new_delta_loc = { 1,0 };
			if (delta_loc != -new_delta_loc || m_snake.getLenght() <= 2)
				delta_loc = new_delta_loc;
		}
	}
}

void SnakeGame::draw(sf::RenderTarget & target) const
{
	if (!gameOver)
	{
		board.drawBoard(target);
		m_snake.draw(target);
		m_apple.draw(target);
	}
	if (gameOver)
	{
		buttonHandler.draw(target);
	}
	target.draw(score);
}
