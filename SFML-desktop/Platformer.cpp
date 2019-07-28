#include "stdafx.h"
#include "Platformer.hpp"
#include "StateHandler.hpp"

Platformer::Platformer() 
	:
	m_player(50, 50, sf::Color::Green, m_cameraControl),
	m_stringArr{ "Unmovable", "Jumpable", "Gap" }
{
}

Platformer::~Platformer()
{
}

void Platformer::init(sf::Window &window, StateHandler &stateHandler)
{
	auto windowSize = static_cast<sf::Vector2i>(window.getSize());
	m_cameraControl.init(m_renderTexture, m_renderSprite, windowSize);
	m_renderTexture.create(windowSize.x, windowSize.y+1000);
	m_renderSprite.setTexture(m_renderTexture.getTexture());

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

	m_indexText.setFont(m_font);
	m_indexText.setPosition(m_prevText.getPosition().x + 400, m_currText.getPosition().y);

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

	m_platformHandler.addPlatform(); // Initialize with a single platform, player can spawn according to
	m_player.setPosition(80, m_platformHandler.platforms().front().getPosition().y - m_player.getSize().y);
}

void Platformer::updateModel(sf::Window &window, StateHandler &stateHandler)
{
	m_dt = std::min(m_clock.restart().asMilliseconds(), 100);
	m_player.update(static_cast<float>(m_dt));
	m_platformHandler.update(m_player);
	m_cameraControl.setCentrePos(static_cast<sf::IntRect>(m_player.getGlobalBounds()));

	auto currZone = m_platformHandler.getCurrZone();
	auto prevZone = m_platformHandler.getPrevZone();
	auto index = m_platformHandler.getIndex();

	m_indexText.setString(std::to_string(index));

	if (m_player.getCalculatedY() > m_platformHandler.platforms()[index].getPosition().y &&
		m_player.getCalculatedY() < m_platformHandler.platforms()[index].getPosition().y + m_player.getSize().y &&
		currZone == PlatformHandler::Zone::Unmovable &&	prevZone == PlatformHandler::Zone::Jumpable)
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
			m_player.move(0, m_gravity * m_dt);
	}
	else if ((currZone == PlatformHandler::Zone::Gap ||
		currZone == PlatformHandler::Zone::Unmovable &&
		prevZone == PlatformHandler::Zone::Gap) && !m_player.isJumping())
	{													
		m_player.move(0, m_gravity * m_dt);
	}
}

void Platformer::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	auto index = m_platformHandler.getIndex();

	m_keyHandler.handleKeyInput();
	m_buttonHandler.handleInput(window);

	auto currZone = m_platformHandler.getCurrZone();
	auto prevZone = m_platformHandler.getPrevZone();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (currZone != PlatformHandler::Zone::Unmovable ||
			(currZone == PlatformHandler::Zone::Unmovable && m_lastDir != LastDir::Left))
		{
			m_player.move(-m_speed * m_dt, 0);
			m_lastDir = LastDir::Left;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (currZone != PlatformHandler::Zone::Unmovable ||	
			(currZone == PlatformHandler::Zone::Unmovable && m_lastDir != LastDir::Right))
		{
			m_player.move(m_speed * m_dt, 0);
			m_lastDir = LastDir::Right;
		}
	}

	if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) &&
		m_jumpable))
	{
		m_player.jump(200, m_player.getCalculatedY());
		m_jumpable = false;
		m_lastDir = LastDir::Up;
	}
}

void Platformer::draw(sf::RenderTarget &target) const
{
	m_renderTexture.clear(sf::Color::Black);
	m_platformHandler.draw(m_renderTexture);
	m_player.draw(m_renderTexture);
	m_renderTexture.display();

	target.draw(m_renderSprite);

	target.draw(m_currText);
	target.draw(m_prevText);
	target.draw(m_currArr[(int)m_platformHandler.getCurrZone()]);
	target.draw(m_prevArr[(int)m_platformHandler.getPrevZone()]);
	target.draw(m_indexText);
}
