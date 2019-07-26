#include "stdafx.h"
#include "PlatformHandler.hpp"


PlatformHandler::PlatformHandler()
{
}


PlatformHandler::~PlatformHandler()
{
}

void PlatformHandler::setSpacing(unsigned int spacing)
{
	m_spacing = spacing;
}

void PlatformHandler::setDefaultSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void PlatformHandler::setNextPos(int x, int y)
{
	m_xCurr = x;
	m_yCurr = y;
}

void PlatformHandler::setDefaultColor(const sf::Color & color)
{
	m_defaultColor = color;
}

unsigned int PlatformHandler::getSpacing() const
{
	return m_spacing;
}

sf::Vector2i PlatformHandler::getSize() const
{
	return sf::Vector2i(m_width, m_height);
}

sf::Vector2i PlatformHandler::getNextPos() const
{
	return sf::Vector2i(m_xCurr, m_yCurr);
}

sf::Color PlatformHandler::getDefaultColor() const
{
	return m_defaultColor;
}

Platform &PlatformHandler::addPlatform()
{
	auto &platform = m_platforms.emplace_back();

	platform.setSize(std::rand() % 600, std::rand() % 100);
	platform.setColor(sf::Color((std::rand() % 255) + 1, (std::rand() % 255) + 1, (std::rand() % 255) + 1));
	platform.setPosition(m_xCurr, m_yCurr);

	auto bounds = platform.getGlobalBounds();
	m_xCurr = int(bounds.left + bounds.width + std::rand() % 100);

	if (std::rand() % 2)
		m_yCurr = int(bounds.top + bounds.height + std::rand() % 50);
	else
		m_yCurr = int(bounds.top - bounds.height - std::rand() % 50);

	return platform;
}

unsigned int PlatformHandler::getIndex(const Player & player)
{
	for (int i = 0; i < m_platforms.size(); i++)
	{
		if (player.getPosition().x + player.getSize().x > m_platforms[i].getPosition().x &&
			player.getPosition().x < m_platforms[i].getPosition().x + m_platforms[i].getSize().x)
			prevIndex = i;
	}

	return prevIndex;
}

bool PlatformHandler::insideX(const Player & player, unsigned int index) const
{
	if (m_platforms[index].xColliding(player))
		return true;

	return false;
}

bool PlatformHandler::fullyInsideX(const Player & player, unsigned int index) const
{
	if (player.getPosition().x > m_platforms[index].getPosition().x &&
		player.getPosition().x + player.getSize().x < m_platforms[index].getPosition().x + m_platforms[index].getSize().x)
		return true;

	return false;
}

bool PlatformHandler::fullyInsideY(const Player & player, unsigned int index) const
{
	if (player.getPosition().y > m_platforms[index].getPosition().y &&
		player.getPosition().y + player.getSize().y < m_platforms[index].getPosition().y + m_platforms[index].getSize().y)
		return true;

	return false;
}

bool PlatformHandler::onGround(const Player & player, unsigned int index) const
{
	if (player.getCalculatedY() == m_platforms[index].getPosition().y)
		return true;

	return false;
}

void PlatformHandler::moveAll(float x, float y)
{
	for (auto &it : m_platforms)
	{
		it.move(x, y);
	}
}

void PlatformHandler::draw(sf::RenderTarget & target) const
{
	for (auto &platform : m_platforms)
	{
		if (inFocus(platform, target))
			platform.draw(target);
	}
}

PlatformHandler::Zone PlatformHandler::findZone(const Player & player) const
{
	for (auto &it : m_platforms)
	{
		if (it.xColliding(player) && it.yColliding(player))
			return Zone::Unmovable;

		else if (it.xColliding(player) &&
			player.getPosition().y < it.getPosition().y)
			return Zone::Jumpable;
	}
	return Zone::Gap;
}

bool PlatformHandler::inFocus(const Platform & platform, sf::RenderTarget &target) const
{
	if (platform.getPosition().x + platform.getSize().x >= 0 &&
		platform.getPosition().x <= target.getSize().x &&
		platform.getPosition().y + platform.getSize().y >= 0 &&
		platform.getPosition().y <= target.getSize().y)
		return true;

	return false;
}

PlatformHandler::Zone PlatformHandler::getZone(const Player & player) const
{
	if (m_currZone != findZone(player))
		m_prevZone = m_currZone;
	m_currZone = findZone(player);

	return m_currZone;
}

PlatformHandler::Zone PlatformHandler::getPrevZone() const
{
	return m_prevZone;
}
