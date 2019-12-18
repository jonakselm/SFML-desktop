#include "stdafx.h"
#include "SnakeGame.hpp"
#include "StateHandler.hpp"
#include <sstream>
#include "SFML-ext.hpp"

SnakeGame::SnakeGame(int nColors, const sf::Color &startColor, const Snake::ColorInit colorInit, int increment)
	:
	m_nColors(nColors),
	m_startColor(startColor),
	m_colorInit(colorInit),
	m_increment(increment),
	m_snake({ 1,1 }, nColors, startColor, colorInit, increment),
	m_botState(SnakeBot::botState::smart),
	m_snakeBot(sf::Vector2f(float(std::rand() % (int)m_board.getSize().x), float(std::rand() % (int)m_board.getSize().y)), 
		nColors, sf::Color::Blue, Snake::ColorInit::Blue, increment),
	m_apple(m_snake, m_snakeBot)
{
	m_snakeBot.setHeadColor(sf::Color(0, 100, 255));
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
			stateHandler.Switch<SnakeGame>(m_nColors, m_startColor, m_colorInit, m_increment);
		});

	userScore.setFont(font);
	userScore.setPosition(10, 5);

	botScore.setFont(font);
	botScore.setPosition(935, 5);
}

void SnakeGame::updateModel(sf::Window &window, StateHandler &stateHandler)
{
	std::string snakeScore = std::to_string(m_snake.getScore());
	userScore.setString(snakeScore);

	std::string botSnakeScore = std::to_string(m_snakeBot.getScore());
	botScore.setString(botSnakeScore);

	float dt = ft.Mark();
	if ((!m_snake.isDead() || !m_snakeBot.isDead())  && !m_pause)
	{
		snakeMoveCounter += dt;

		if (snakeMoveCounter >= snakeMovePeriod)
		{
			snakeMoveCounter -= snakeMovePeriod;
			const sf::FloatRect nextSnakeBounds = m_snake.getNextBounds(delta_loc);

			if (m_snake.inTileExceptEnd(nextSnakeBounds) ||
				!m_board.insideBoard(nextSnakeBounds) ||
				(m_snakeBot.inTileExceptEnd(nextSnakeBounds) && !m_snakeBot.isDead()))
			m_snake.setDead();

			const sf::FloatRect nextBotBounds = m_snakeBot.getNextBounds(m_snake, m_apple, m_botState);

			if (m_snakeBot.inTileExceptEnd(nextBotBounds) ||
				!m_board.insideBoard(nextBotBounds) ||
				(m_snake.inTileExceptEnd(nextBotBounds) && !m_snake.isDead()))
				m_snakeBot.setDead();

			if (!m_snake.isDead())
			{
				if (m_apple.getGlobalBounds().intersects(m_snake.getNextBounds(delta_loc)))
				{
					m_snake.growAndMoveBy(delta_loc);
					m_apple.respawn(m_snake, m_snakeBot);
				}
				else
				{
					m_snake.moveBy(delta_loc);
				}
			}

			if (!m_snakeBot.isDead())
			{
				if (m_apple.getGlobalBounds().intersects(m_snakeBot.getNextBounds(m_snake, m_apple, m_botState)))
				{
					m_snakeBot.growAndUpdate(m_snake, m_apple, m_botState);
					m_apple.respawn(m_snake, m_snakeBot);
				}
				else
				{
					m_snakeBot.update(m_snake, m_apple, m_botState);
				}
			}
		}

		snakeMovePeriod = std::max(snakeMovePeriod - dt * snakeSpeedupFactor, snakeMovePeriodMin);
	}
}

void SnakeGame::handleExtraEvents(sf::Window &window, StateHandler &stateHandler)
{
	if (sf::Joystick::isButtonPressed(0, sfExt::Ps3::Circle))
		stateHandler.Pop();

	if (m_pausable && sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		m_pause = true;
	else if (m_pause)
		m_pausable = false;
	if (!m_pausable && sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		m_pause = false;
	else if (!m_pause)
		m_pausable = true;

	m_keyHandler.handleKeyInput();
	if (m_snake.isDead() && m_snakeBot.isDead())
		buttonHandler.handleInput(window);

	if (!m_snake.isDead() && !m_pause)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Joystick::isButtonPressed(0, sfExt::Ps3::Up))
		{
			const sf::Vector2f new_delta_loc = { 0,-1 };
			if (delta_loc != -new_delta_loc || m_snake.getLength() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Joystick::isButtonPressed(0, sfExt::Ps3::Down))
		{
			const sf::Vector2f new_delta_loc = { 0,1 };
			if (delta_loc != -new_delta_loc || m_snake.getLength() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Joystick::isButtonPressed(0, sfExt::Ps3::Left))
		{
			const sf::Vector2f new_delta_loc = { -1,0 };
			if (delta_loc != -new_delta_loc || m_snake.getLength() <= 2)
				delta_loc = new_delta_loc;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Joystick::isButtonPressed(0, sfExt::Ps3::Right))
		{
			const sf::Vector2f new_delta_loc = { 1,0 };
			if (delta_loc != -new_delta_loc || m_snake.getLength() <= 2)
				delta_loc = new_delta_loc;
		}
	}
}

void SnakeGame::draw(sf::RenderTarget & target) const
{
	if (!m_snake.isDead() || !m_snakeBot.isDead())
	{
		m_board.drawBoard(target);
		m_apple.draw(target);
	}
	else if (m_snake.isDead() && m_snakeBot.isDead())
	{
		buttonHandler.draw(target);
	}
	if (!m_snakeBot.isDead())
	{
		m_snakeBot.draw(target);
	}
	if (!m_snake.isDead())
	{
		m_snake.draw(target);
	}

	target.draw(userScore);
	target.draw(botScore);
}
