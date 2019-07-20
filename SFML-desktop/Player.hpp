#pragma once

#include "Shape.hpp"

class Player : public Shape
{
public:
	Player(float x, float y);
	virtual ~Player();

	sf::FloatRect getGlobalBounds() const;

	void draw(sf::RenderTarget &target) const;

private:
	sf::RectangleShape player;
};

