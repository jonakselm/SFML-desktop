#pragma once

#include "Shape.hpp"
#include "Snake.h"
#include "Board.h"

class SnakeBot : public Snake
{
public:
	SnakeBot(const sf::Vector2f& loc, int nColors, const sf::Color& startColor, const Snake::ColorInit colorInit, int increment);
	~SnakeBot();

	void update(Snake& otherSnake, class Apple& apple);
	void growAndUpdate(Snake& otherSnake, Apple& apple);

	sf::FloatRect getNextBounds(Snake& otherSnake, Apple& apple);
	sf::Vector2f getNextLoc(Snake& otherSnake, Apple& apple);

private:
	bool isSafe(const Snake& otherSnake, const sf::Vector2f& delta_loc);
	sf::Vector2f getDeltaLoc(Snake& otherSnake, Apple& apple);

private:
	Board m_board;

	sf::Vector2f prevLoc;

	const sf::Vector2f left = { -1,0 }, right = { 1,0 }, up = { 0,-1 }, down = { 0,1 };
};

