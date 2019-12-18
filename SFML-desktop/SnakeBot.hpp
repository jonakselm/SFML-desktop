#pragma once

#include "Shape.hpp"
#include "Snake.h"
#include "Board.h"

class SnakeBot : public Snake
{
public:
	enum class botState { dumb, smart };
	enum class direction { up, down, left, right };
	SnakeBot(const sf::Vector2f& loc, int nColors, const sf::Color& startColor, const Snake::ColorInit colorInit, int increment);
	~SnakeBot();

	void update(Snake& otherSnake, class Apple& apple, botState state);
	void growAndUpdate(Snake& otherSnake, Apple& apple, botState state);

	sf::FloatRect getNextBounds(Snake& otherSnake, Apple& apple, botState state);
	sf::Vector2f getNextLoc(Snake& otherSnake, Apple& apple, botState state);

private:
	bool isSafe(const Snake& otherSnake, const direction dir);
	sf::Vector2f getDeltaLoc(Snake& otherSnake, Apple& apple, botState state);

private:
	Board m_board;

	sf::Vector2f prevLoc;

	//const sf::Vector2f left = { -1,0 }, right = { 1,0 }, up = { 0,-1 }, down = { 0,1 };
};

