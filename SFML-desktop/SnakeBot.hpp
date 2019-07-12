#pragma once

#include "Shape.hpp"
#include "Snake.h"
#include "Board.h"

class SnakeBot : public Shape
{
public:
	SnakeBot(const sf::Vector2f& loc, int nColors, sf::Color& startColor, Snake::ColorInit colorInit, int increment);
	~SnakeBot();

	void update(Snake& otherSnake, class Apple& apple);
	bool isDead() const;
	bool inTile(sf::Vector2f& locTarget);
	void growAndMoveBy(Snake& otherSnake, Apple& apple);

	void draw(sf::RenderTarget& target) const;

	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getNextBounds(Snake& otherSnake, Apple& apple);
	sf::Vector2f getHeadLoc() const;
	int getScore() const;

private:
	bool isSafe(const Snake& otherSnake, const sf::Vector2f& delta_loc);
	sf::Vector2f getDeltaLoc(Snake& otherSnake, Apple& apple);

private:
	Snake m_snake;
	Board m_board;

	sf::Vector2f prevLoc;

	const sf::Vector2f left = { -1,0 }, right = { 1,0 }, up = { 0,-1 }, down = { 0,1 };

	bool dead = false;
};

