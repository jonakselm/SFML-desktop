#pragma once

#include "Shape.hpp"

class Platform : public Shape
{
public:
	Platform();
	virtual ~Platform();

	void setPosition(int x, int y);
	void setSize(int x, int y);
	void setColor(const sf::Color &color);
	void move(float x, float y);

	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	bool xColliding(const class PlatformPlayer &player) const;
	bool yColliding(const class PlatformPlayer &player) const;

	void draw(sf::RenderTarget &target) const;

private:
	sf::RectangleShape m_platform;
};

