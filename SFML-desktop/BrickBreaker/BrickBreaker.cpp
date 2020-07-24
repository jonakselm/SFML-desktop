#include "stdafx.h"
#include "BrickBreaker.hpp"
#include <sstream>
#include "../StateHandler.hpp"

BrickBreaker::BrickBreaker()
	:
	m_brickGrid(16, 12)
{
}

BrickBreaker::~BrickBreaker()
{
}

void BrickBreaker::init(sf::Window &window, StateHandler &stateHandler)
{
	keyHandler.onKeyPressed(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});
	keyHandler.onKeyPressed(sf::Keyboard::R, [&]
		{
			stateHandler.Switch<BrickBreaker>();
		});

	m_font.loadFromFile("data/fonts/Georgia.ttf");

	m_elapsedTimeText.setFont(m_font);
	m_elapsedTimeText.setPosition(5, 5);

	m_ballPosText.setFont(m_font);
	m_ballPosText.setPosition(5, 35);
}

void BrickBreaker::updateModel(sf::Window &window, StateHandler &stateHandler)
{
	m_elapsedTime = m_clock.restart();
	m_ball.update(m_elapsedTime.asSeconds());

	if (m_ball.getGlobalBounds().intersects(m_pad.getGlobalBounds()))
	{
		if (m_ball.intersectCenterX(m_pad.getGlobalBounds()))
			m_ball.reboundY();
		else
			m_ball.reboundX();
	}

	if (m_ball.getPosition().x < 0)
	{
		float offsetX = m_ball.getPosition().x - 0;
		m_ball.move(-offsetX, 0);
		m_ball.reboundX();
	}
	else if (m_ball.getPosition().x + (m_ball.getRadius() * 2) > 990)
	{
		float offsetX = m_ball.getPosition().x + m_ball.getRadius() * 2 - 990;
		m_ball.move(-offsetX, 0);
		m_ball.reboundX();
	}
	else if (m_ball.getPosition().y < 0)
	{
		float offsetY = m_ball.getPosition().y - 0;
		m_ball.move(0, -offsetY);
		m_ball.reboundY();
	}
	else if (m_ball.getPosition().y + (m_ball.getRadius() * 2) > 900)
	{
		float offsetY = m_ball.getPosition().y + m_ball.getRadius() * 2 - 900;
		m_ball.move(0, -offsetY);
		m_ball.reboundY();
	}

	for (int y = 0; y < m_brickGrid.getGridSize().y; y++)
	{
		for (int x = 0; x < m_brickGrid.getGridSize().x; x++)
		{
			const Brick &brick = m_brickGrid.getBrick(x, y);
			if (!brick.destroyed &&
				m_ball.getGlobalBounds().intersects(brick.shape.getGlobalBounds()))
			{
				m_brickGrid.popBrick(x, y);

				if (m_ball.intersectCenterX(brick.shape.getGlobalBounds()))
					m_ball.reboundY();
				else
					m_ball.reboundX();
			}
		}
	}

	std::stringstream ss, ss1;

	ss << "Elapsed Time: " << m_elapsedTime.asSeconds();
	m_elapsedTimeText.setString(ss.str());

	ss1 << "X: " << m_ball.getPosition().x << ", Y: " << m_ball.getPosition().y;
	m_ballPosText.setString(ss1.str());
}

void BrickBreaker::handleExtraEvents(sf::Window &window, StateHandler &stateHandler)
{
	keyHandler.handleKeyInput();

	if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < 990 &&
		sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < 900)
		m_pad.setCenterPos(sf::Mouse::getPosition(window).x, m_pad.getCenterPos().y);
}

void BrickBreaker::draw(sf::RenderTarget &target)
{
	m_brickGrid.draw(target);
	m_pad.draw(target);
	m_ball.draw(target);

	target.draw(m_elapsedTimeText);
	target.draw(m_ballPosText);
}
