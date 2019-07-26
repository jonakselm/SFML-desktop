#pragma once

#include "Platform.hpp"
#include <vector>
#include "Player.hpp"

class PlatformHandler
{
public:
	enum class Zone { Unmovable, Jumpable, Gap };

public:
	PlatformHandler();
	~PlatformHandler();

	void setSpacing(unsigned int spacing);
	void setDefaultSize(int width, int height);
	void setNextPos(int x, int y);
	void setDefaultColor(const sf::Color &color);

	unsigned int getSpacing() const;
	sf::Vector2i getSize() const;
	sf::Vector2i getNextPos() const;
	sf::Color getDefaultColor() const;

	Platform &addPlatform();

	unsigned int getIndex(const Player &player);
	bool insideX(const Player &player, unsigned int index) const;
	bool fullyInsideX(const Player &player, unsigned int index) const;
	bool fullyInsideY(const Player &player, unsigned int index) const;
	bool onGround(const Player &player, unsigned int index) const;

	Zone getZone(const Player &player) const;
	Zone getPrevZone() const;

	auto &platforms() { return m_platforms; }
	const auto &platforms() const { return m_platforms; }
	void moveAll(float x, float y);

	void draw(sf::RenderTarget &target) const;

private:
	Zone findZone(const Player &player) const;
	bool inFocus(const Platform &platform, sf::RenderTarget &target) const;

private:
	int m_width = 500, m_height = 500 ;
	int m_xCurr = 0, m_yCurr = 500;
	int m_spacing = 75;
	unsigned int prevIndex;
	sf::Color m_defaultColor = sf::Color(139, 69, 19);
	std::vector<Platform> m_platforms;
	mutable Zone m_prevZone = Zone::Unmovable, m_currZone = Zone::Unmovable;
};

