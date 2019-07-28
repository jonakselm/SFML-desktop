#include "stdafx.h"
#include "Platform.hpp"
#include "Player.hpp"

Platform::Platform()
{
}


Platform::~Platform()
{
}

void Platform::setPosition(int x, int y)
{
	m_platform.setPosition((float)x, (float)y);
}

void Platform::setSize(int x, int y)
{
	m_platform.setSize(sf::Vector2f((float)x, (float)y));
}

void Platform::setColor(const sf::Color &color)
{
	m_platform.setFillColor(color);
}

sf::FloatRect Platform::getGlobalBounds() const
{
	return m_platform.getGlobalBounds();
}

sf::Vector2f Platform::getPosition() const
{
	return m_platform.getPosition();
}

sf::Vector2f Platform::getSize() const
{
	return m_platform.getSize();
}

bool Platform::xColliding(const Player & player) const
{
	return player.getPosition().x + player.getSize().x > m_platform.getPosition().x &&
		player.getPosition().x < m_platform.getPosition().x + m_platform.getSize().x;
}

bool Platform::yColliding(const Player & player) const
{
	return player.getPosition().y + player.getSize().y > m_platform.getPosition().y &&
		player.getPosition().y < m_platform.getPosition().y + m_platform.getSize().y;
}

void Platform::draw(sf::RenderTarget & target) const
{
	target.draw(m_platform);
}
