#pragma once
#include "Shape.hpp"
#include "Board.h"
#include "Snake.h"
#include "SnakeBot.hpp"

class Apple : public Shape
{
public:
	Apple(Snake& snake, SnakeBot &snakeBot);
	void respawn(Snake& snake, SnakeBot &snakeBot);

	void draw(sf::RenderTarget &target) const override;
	sf::FloatRect getGlobalBounds() const override;
	sf::Vector2f getLocation() const;

private:
	Board m_board;
	sf::CircleShape m_shape;

	sf::Vector2f loc;
};