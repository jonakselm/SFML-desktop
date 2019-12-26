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

void SnakeBot::update(Snake & otherSnake, Apple & apple, botState state)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple, state);
	prevLoc = delta_loc;

	Snake::moveBy(delta_loc);
}

void SnakeBot::growAndUpdate(Snake & otherSnake, Apple & apple, botState state)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple, state);
	prevLoc = delta_loc;

	Snake::growAndMoveBy(delta_loc);
}

sf::Vector2f SnakeBot::getDeltaLoc(Snake & otherSnake, Apple & apple, botState state)
{
	sf::Vector2f delta_loc;

	if (state == botState::smart)
	{
		// First line of the if/else statements test if the location is safe,
		// and if the apple's location is higher or lower than the snake's location.
		// It tests the x axis for left and right, and y axis for up and down.
		//
		// The second line tests if the apple is in a location where the 
		// snake can't go directly to the apple and has to take a u-turn.
		// If the apple is upwards and the snake's body is directly upwards,
		// the snake tries to find a way around its body instead of commiting suicide.

		sf::FloatRect appleBounds = apple.getGlobalBounds();
		sf::FloatRect botBounds = Snake::getGlobalBounds();

		if (isSafe(otherSnake, direction::left) && ((appleBounds.left < botBounds.left) ||
			(appleBounds.top < botBounds.top && !isSafe(otherSnake, direction::up))))
			delta_loc = { -1, 0 };
		else if (isSafe(otherSnake, direction::right) && ((appleBounds.left + appleBounds.width > botBounds.left + botBounds.width) ||
			(appleBounds.top > botBounds.top + botBounds.height && !isSafe(otherSnake, direction::down))))
			delta_loc = { 1, 0 };
		else if (isSafe(otherSnake, direction::up) && ((appleBounds.top < botBounds.top) ||
			(appleBounds.left < botBounds.left && !isSafe(otherSnake, direction::left))))
			delta_loc = { 0, -1 };
		else if (isSafe(otherSnake, direction::down) && ((appleBounds.top + appleBounds.height > botBounds.top + botBounds.height) ||
			(appleBounds.left > botBounds.left + botBounds.width && !isSafe(otherSnake, direction::right))))
			delta_loc = { 0, 1 };

		return delta_loc;
	}
	else if (state == botState::dumb)
	{
		direction dir = direction(std::rand() % 4);

		if (isSafe(otherSnake, (direction)dir))
		{
			switch (dir)
			{
			case direction::up:
				delta_loc = { 0, -1 };
				break;
			case direction::down:
				delta_loc = { 0, 1 };
				break;
			case direction::left:
				delta_loc = { -1, 0 };
				break;
			case direction::right:
				delta_loc = { 1, 0 };
				break;
			}
			return delta_loc;
		}
		else
			return prevLoc;
	}
	else
		return prevLoc;
}

sf::FloatRect SnakeBot::getNextBounds(Snake& otherSnake, Apple& apple, botState state)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple, state);

	return Snake::getNextBounds(delta_loc);
}

sf::Vector2f SnakeBot::getNextLoc(Snake & otherSnake, Apple & apple, botState state)
{
	return Snake::getNextLoc(getDeltaLoc(otherSnake, apple, state));
}

bool SnakeBot::isSafe(const Snake& otherSnake, const direction dir)
{
	sf::Vector2f delta_loc;

	switch (dir)
	{
	case direction::up:
		delta_loc = { 0, -1 };
		break;
	case direction::down:
		delta_loc = { 0, 1 };
		break;
	case direction::left:
		delta_loc = { -1, 0 };
		break;
	case direction::right:
		delta_loc = { 1, 0 };
		break;
	}

	const sf::FloatRect nextBounds = Snake::getNextBounds(delta_loc);

	if (!Snake::inTileExceptEnd(nextBounds) &&
		m_board.insideBoard(nextBounds) &&
		(!otherSnake.inTileExceptEnd(nextBounds) || otherSnake.isDead()))
	{
		return true;
	}
	return false;
}
