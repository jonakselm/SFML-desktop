#include "stdafx.h"
#include "SnakeGame.hpp"
#include "StateHandler.hpp"
#include <sstream>

SnakeGame::SnakeGame()
	:
	lastTime(0),
	snake ({ 1,1 })
{
}


SnakeGame::~SnakeGame()
{
}

void SnakeGame::init(sf::Window & window, StateHandler & stateHandler)
{
	auto &kEsc = keyHandler.addKey(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});

	font.loadFromFile("data/fonts/Georgia.ttf");
	buttonHandler.setDefaultSize(200, 100);
	buttonHandler.setFont(font);
	buttonHandler.setNextPosition(450, 400);

	auto &bRestart = buttonHandler.addButton("Game Over!\nRestart?", [&]
		{
			stateHandler.Switch<SnakeGame>();
		});

	score.setFont(font);
	score.setPosition(10, 5);
}

void SnakeGame::updateModel(sf::Window &window, StateHandler &stateHandler)
{
	std::stringstream ss;
	ss << snake.GetScore();
	score.setString(ss.str());

	float dt = ft.Mark();
	if (!gameOver)
	{
		snakeMoveCounter += dt;
		int64_t time = 200'000;
		if (snakeMoveCounter >= (snakeMovePeriod + lastTime))
		{
			lastTime += (int64_t)dt;
			snakeMoveCounter -= snakeMovePeriod;
			const sf::Vector2f next = snake.nextHeadLoc(delta_loc);

			if (snake.inTileExceptEnd(next) ||
				!board.InsideBoard(next))
			gameOver = true;

			if (m_apple.getGlobalBounds().intersects(snake.getNextBounds(delta_loc)))
			{
				snake.GrowAndMoveBy(delta_loc);
				m_apple.respawn();

			}
			else
			{
				snake.MoveBy(delta_loc);
			}
		}

		snakeMovePeriod = std::max(snakeMovePeriod - dt * snakeSpeedupFactor, snakeMovePeriodMin);
	}
}

void SnakeGame::handleExtraEvents(sf::Window &window, StateHandler &stateHandler)
{
	keyHandler.handleKeyInput();
	if (gameOver)
		buttonHandler.handleInput(window);

	if (!gameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			const sf::Vector2f new_delta_loc = { 0,-1 };
			if (delta_loc != -new_delta_loc || snake.GetLenght() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			const sf::Vector2f new_delta_loc = { 0,1 };
			if (delta_loc != -new_delta_loc || snake.GetLenght() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			const sf::Vector2f new_delta_loc = { -1,0 };
			if (delta_loc != -new_delta_loc || snake.GetLenght() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			const sf::Vector2f new_delta_loc = { 1,0 };
			if (delta_loc != -new_delta_loc || snake.GetLenght() <= 2)
				delta_loc = new_delta_loc;
		}
	}
}

void SnakeGame::draw(sf::RenderTarget & target)
{
	if (!gameOver)
	{
		board.drawBoard(target);
		m_apple.draw(target);
		snake.draw(target);
	}
	if (gameOver)
	{
		buttonHandler.draw(target);
	}
	target.draw(score);
}
