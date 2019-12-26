#include "stdafx.h"
#include "PlatformHandler.hpp"

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

unsigned int PlatformHandler::getIndex() const
{
	return m_currIndex;
}

bool PlatformHandler::insideBounds(const PlatformPlayer & player, unsigned int index) const
{
	if (m_platforms[index].xColliding(player) && m_platforms[index].yColliding(player))
		return true;

	return false;
}

bool PlatformHandler::insideX(const PlatformPlayer & player, unsigned int index) const
{
	if (m_platforms[index].xColliding(player))
		return true;

	return false;
}

bool PlatformHandler::fullyInsideX(const PlatformPlayer & player, unsigned int index) const
{
	if (player.getPosition().x > m_platforms[index].getPosition().x &&
		player.getPosition().x + player.getSize().x < m_platforms[index].getPosition().x + m_platforms[index].getSize().x)
		return true;

	return false;
}

bool PlatformHandler::fullyInsideY(const PlatformPlayer & player, unsigned int index) const
{
	if (player.getPosition().y > m_platforms[index].getPosition().y &&
		player.getPosition().y + player.getSize().y < m_platforms[index].getPosition().y + m_platforms[index].getSize().y)
		return true;

	return false;
}

bool PlatformHandler::onGround(const PlatformPlayer &player, unsigned int index) const
{
	if (player.getCalculatedY() == m_platforms[index].getPosition().y)
		return true;

	return false;
}

void PlatformHandler::draw(sf::RenderTarget &target) const
{
	for (auto &platform : m_platforms)
	{
		if (inFocus(platform, target))
			platform.draw(target);
	}
}

PlatformHandler::Zone PlatformHandler::findZone(const PlatformPlayer & player) const
{
	for (auto &platform : m_platforms)
	{
		if (platform.xColliding(player) && platform.yColliding(player))
			return Zone::Unmovable;

		else if (platform.xColliding(player) &&
			player.getPosition().y < platform.getPosition().y)
			return Zone::Jumpable;
	}

	return Zone::Gap;
}

bool PlatformHandler::inFocus(const Platform &platform, sf::RenderTarget &target) const
{
	if (platform.getPosition().x + platform.getSize().x >= 0 &&
		platform.getPosition().x <= target.getSize().x &&
		platform.getPosition().y + platform.getSize().y >= 0 &&
		platform.getPosition().y <= target.getSize().y)
		return true;

	return false;
}

void PlatformHandler::update(const PlatformPlayer &player)
{
	// Update zones
	if (m_currZone != findZone(player))
		m_prevZone = m_currZone;
	m_currZone = findZone(player);

	// Find current index
	for (int i = 0; i < m_platforms.size(); i++)
	{
		if (m_platforms[i].xColliding(player))
			m_currIndex = i;
	}

	// Always generate new platforms
	while (m_currIndex + 10 > m_platforms.size())
		addPlatform();
}

PlatformHandler::Zone PlatformHandler::getCurrZone() const
{
	return m_currZone;
}

PlatformHandler::Zone PlatformHandler::getPrevZone() const
{
	return m_prevZone;
}
