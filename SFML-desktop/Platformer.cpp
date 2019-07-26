#include "stdafx.h"
#include "Platformer.hpp"
#include "StateHandler.hpp"

Platformer::Platformer()
	:
	m_player(50, 50, sf::Color::Green),
	m_cameraControl(m_player, m_platformHandler),
	m_stringArr{ "Unmovable", "Jumpable", "Gap" }
{
}

Platformer::~Platformer()
{
}

void Platformer::init(sf::Window & window, StateHandler & stateHandler)
{
	m_keyHandler.addKey(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});

	m_font.loadFromFile("data/fonts/georgia.ttf");

	m_currText.setFont(m_font);
	m_prevText.setFont(m_font);

	m_currText.setString("Current Zone");
	m_prevText.setString("Previous Zone");

	m_currText.setPosition(5, 5);
	m_currArr.front().setPosition(m_currText.getPosition().x, m_currText.getPosition().y + 50);

	m_prevText.setPosition(m_currText.getPosition().x + 400, m_currText.getPosition().y);
	m_prevArr.front().setPosition(m_prevText.getPosition().x, m_prevText.getPosition().y + 50);

	m_currArr.front().setFont(m_font);
	m_prevArr.front().setFont(m_font);

	m_currArr.front().setString(m_stringArr.front());
	m_prevArr.front().setString(m_stringArr.front());

	for (int i = 1; i < 3; i++)
	{
		m_currArr[i].setFont(m_font);
		m_prevArr[i].setFont(m_font);

		m_currArr[i].setPosition(m_currArr.front().getPosition().x, m_currArr.front().getPosition().y);
		m_prevArr[i].setPosition(m_prevArr.front().getPosition().x, m_prevArr.front().getPosition().y);

		m_currArr[i].setString(m_stringArr[i]);
		m_prevArr[i].setString(m_stringArr[i]);
	}

	m_platformHandler.setNextPos(0, 300);
	m_platformHandler.addPlatform();
	//m_platformHandler.setNextPos(m_platformHandler.getNextPos().x, 450);
	for (int i = 0; i < 100; i++)
	m_platformHandler.addPlatform();

	m_player.setPosition(80, m_platformHandler.platforms().front().getPosition().y - m_player.getSize().y);
}

void Platformer::updateModel(sf::Window & window, StateHandler & stateHandler)
{
	float dt = (float)m_clock.restart().asMilliseconds();

	m_player.update(dt);

	auto currZone = m_platformHandler.getZone(m_player);
	auto prevZone = m_platformHandler.getPrevZone();

	auto index = m_platformHandler.getIndex(m_player);

	if (m_player.getCalculatedY() > m_platformHandler.platforms()[index].getPosition().y &&
		currZone == PlatformHandler::Zone::Unmovable &&
		prevZone == PlatformHandler::Zone::Jumpable)
	{
		m_player.setCalculatedY(m_platformHandler.platforms()[index].getPosition().y);
	}

	if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) &&
		m_platformHandler.onGround(m_player, index) &&
		currZone == PlatformHandler::Zone::Jumpable)
	{
		m_jumpable = true;
	}

	if (m_lastDir == LastDir::Left && currZone == PlatformHandler::Zone::Unmovable &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		prevZone == PlatformHandler::Zone::Gap)
		m_player.move(1, 0);
	else if (m_lastDir == LastDir::Right && currZone == PlatformHandler::Zone::Unmovable &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		prevZone == PlatformHandler::Zone::Gap)
		m_player.move(-1, 0);

	if (currZone == PlatformHandler::Zone::Jumpable)
	{
		if (m_player.getCalculatedY() < m_platformHandler.platforms()[index].getPosition().y &&
			!m_player.isJumping())
			m_player.move(0, m_gravity * dt);
	}
	else if ((currZone == PlatformHandler::Zone::Gap ||
		currZone == PlatformHandler::Zone::Unmovable &&
		prevZone == PlatformHandler::Zone::Gap) && !m_player.isJumping())
	{													
		m_player.move(0, m_gravity * dt);
	}
}

void Platformer::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	float dt = (float)m_clock.getElapsedTime().asMilliseconds();

	auto index = m_platformHandler.getIndex(m_player);

	m_keyHandler.handleKeyInput();
	m_buttonHandler.handleInput(window);

	auto currZone = m_platformHandler.getZone(m_player);
	auto prevZone = m_platformHandler.getPrevZone();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_cameraControl.move(0, m_speed * dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_cameraControl.move(m_speed * dt, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_cameraControl.move(0, -m_speed * dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_cameraControl.move(-m_speed * dt, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (currZone != PlatformHandler::Zone::Unmovable)
		{
			if (m_player.getPosition().x + m_player.getSize().x < window.getSize().x / 2
				&& m_platformHandler.platforms().front().getPosition().x < 0)
				m_cameraControl.move(m_speed * dt, 0);
			m_player.move(-m_speed * dt, 0);
			m_lastDir = LastDir::Left;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (currZone != PlatformHandler::Zone::Unmovable)
		{
			if (m_player.getPosition().x > window.getSize().x / 2
				&& m_platformHandler.platforms().back().getPosition().x > window.getSize().x)
				m_cameraControl.move(-m_speed * dt, 0);
			m_player.move(m_speed * dt, 0);
			m_lastDir = LastDir::Right;
		}
	}

	if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) &&
		m_jumpable && currZone == PlatformHandler::Zone::Jumpable))
	{
		m_player.jump(200, m_platformHandler.platforms()[index].getPosition().y);
		m_jumpable = false;
		m_lastDir = LastDir::Up;
	}
}

void Platformer::draw(sf::RenderTarget & target) const
{
	m_platformHandler.draw(target);
	m_player.draw(target);

	target.draw(m_currText);
	target.draw(m_prevText);
	target.draw(m_currArr[(int)m_platformHandler.getZone(m_player)]);
	target.draw(m_prevArr[(int)m_platformHandler.getPrevZone()]);
}
