#pragma once

#include "Platform.hpp"
#include "PlatformPlayer.hpp"

class PlatformHandler
{
public:
	enum class Zone { Unmovable, Jumpable, Gap };

public:
	Platform &addPlatform();

	bool insideBounds(const PlatformPlayer &player, unsigned int index) const;
	bool insideX(const PlatformPlayer &player, unsigned int index) const;
	bool fullyInsideX(const PlatformPlayer &player, unsigned int index) const;
	bool fullyInsideY(const PlatformPlayer &player, unsigned int index) const;
	bool onGround(const PlatformPlayer &player, unsigned int index) const;

	void update(const PlatformPlayer &player);
	Zone getCurrZone() const;
	Zone getPrevZone() const;
	unsigned int getIndex() const;

	auto &platforms() { return m_platforms; }
	const auto &platforms() const { return m_platforms; }

	void draw(sf::RenderTarget &target) const;

private:
	Zone findZone(const PlatformPlayer &player) const;
	bool inFocus(const Platform &platform, sf::RenderTarget &target) const;

private:
	int m_xCurr = 0, m_yCurr = 500;
	std::vector<Platform> m_platforms;
	unsigned int m_currIndex;
	Zone m_prevZone, m_currZone;
};

