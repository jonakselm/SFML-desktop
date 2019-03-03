#pragma once
#include "Shape.hpp"

class Apple : public Shape
{
public:
	Apple();
	void respawn();

	void draw(sf::RenderTarget &target) const override;
	sf::FloatRect getGlobalBounds() const override;
private:
	sf::CircleShape m_shape;
};