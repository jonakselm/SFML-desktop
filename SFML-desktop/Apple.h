#pragma once
#include "Shape.hpp"
#include "Board.h"

class Apple : public Shape
{
public:
	Apple();
	void respawn();

	void draw(sf::RenderTarget &target) const override;
	sf::FloatRect getGlobalBounds() const override;
private:
	Board board;
	sf::CircleShape m_shape;
};