#include "stdafx.h"
#include "SnakeBot.hpp"
#include "Apple.h"


SnakeBot::SnakeBot(const sf::Vector2f & loc, int nColors, const sf::Color & startColor, const Snake::ColorInit colorInit, int increment)
	:
	Snake(loc, nColors, startColor, colorInit, increment)
{
}

SnakeBot::~SnakeBot()
{
}

void SnakeBot::update(Snake & otherSnake, Apple & apple)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple);
	prevLoc = delta_loc;

	Snake::moveBy(delta_loc);
}

void SnakeBot::growAndUpdate(Snake & otherSnake, Apple & apple)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple);
	prevLoc = delta_loc;

	Snake::growAndMoveBy(delta_loc);
}

sf::Vector2f SnakeBot::getDeltaLoc(Snake & otherSnake, Apple & apple)
{
	sf::Vector2f delta_loc;

	// First line of the if/else statements test if the location is safe,
	// and if the apple's location is higher or lower than the snake's location.
	// It tests the x axis for left and right, and y axis for up and down.
	//
	// The second line tests if the apple is in a location where the 
	// snake can't go directly to the apple and has to take a u-turn.
	// If the apple is upwards and the snake's body is directly upwards,
	// the snake tries to find a way around its body instead of commiting suicide.
	
	if (isSafe(otherSnake, left) && ((apple.getLocation().x < Snake::getHeadLoc().x) ||
		(apple.getLocation().y < Snake::getHeadLoc().y && !isSafe(otherSnake, up))))
		delta_loc = left;
	else if (isSafe(otherSnake, right) && ((apple.getLocation().x > Snake::getHeadLoc().x) ||
		(apple.getLocation().y > Snake::getHeadLoc().y && !isSafe(otherSnake, down))))
		delta_loc = right;
	else if (isSafe(otherSnake, up) && ((apple.getLocation().y < Snake::getHeadLoc().y) ||
		(apple.getLocation().x < Snake::getHeadLoc().x && !isSafe(otherSnake, left))))
		delta_loc = up;
	else if (isSafe(otherSnake, down) && ((apple.getLocation().y > Snake::getHeadLoc().y) ||
		(apple.getLocation().x < Snake::getHeadLoc().x && !isSafe(otherSnake, right))))
		delta_loc = down;
	else
		delta_loc = prevLoc;

	return delta_loc;
}

sf::FloatRect SnakeBot::getNextBounds(Snake& otherSnake, Apple& apple)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple);

	return Snake::getNextBounds(delta_loc);
}

sf::Vector2f SnakeBot::getNextLoc(Snake & otherSnake, Apple & apple)
{
	return Snake::getNextLoc(getDeltaLoc(otherSnake, apple));
}

bool SnakeBot::isSafe(const Snake& otherSnake, const sf::Vector2f& delta_loc)
{
	const sf::Vector2f next = Snake::getNextLoc(delta_loc);

	if (!Snake::inTileExceptEnd(next) &&
		m_board.insideBoard(next) &&
		(!otherSnake.inTileExceptEnd(next) || otherSnake.isDead()))
	{
		return true;
	}
	return false;
}
