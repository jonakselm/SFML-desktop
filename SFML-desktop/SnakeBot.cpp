#include "stdafx.h"
#include "SnakeBot.hpp"
#include "Apple.h"


SnakeBot::SnakeBot(const sf::Vector2f & loc, int nColors, sf::Color & startColor, Snake::ColorInit colorInit, int increment)
	:
	m_snake(loc, nColors, startColor, colorInit, increment)
{
}

SnakeBot::~SnakeBot()
{
}

void SnakeBot::update(Snake & otherSnake, Apple & apple)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple);
	prevLoc = delta_loc;

	if (m_snake.inTileExceptEnd(m_snake.getNextLoc(delta_loc)) ||
		!m_board.insideBoard(m_snake.getNextLoc(delta_loc)))
		dead = true;

	m_snake.moveBy(delta_loc);
}

bool SnakeBot::isDead() const
{
	return dead;
}

bool SnakeBot::inTile(sf::Vector2f & locTarget)
{
	return m_snake.inTile(locTarget);
}

void SnakeBot::growAndMoveBy(Snake & otherSnake, Apple & apple)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple);
	prevLoc = delta_loc;

	m_snake.growAndMoveBy(delta_loc);
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
	
	if (isSafe(otherSnake, left) && ((apple.getLocation().x < m_snake.getHeadLoc().x) ||
		(apple.getLocation().y < m_snake.getHeadLoc().y && !isSafe(otherSnake, up))))
		delta_loc = left;
	else if (isSafe(otherSnake, right) && ((apple.getLocation().x > m_snake.getHeadLoc().x) ||
		(apple.getLocation().y > m_snake.getHeadLoc().y && !isSafe(otherSnake, down))))
		delta_loc = right;
	else if (isSafe(otherSnake, up) && ((apple.getLocation().y < m_snake.getHeadLoc().y) ||
		(apple.getLocation().x < m_snake.getHeadLoc().x && !isSafe(otherSnake, left))))
		delta_loc = up;
	else if (isSafe(otherSnake, down) && ((apple.getLocation().y > m_snake.getHeadLoc().y) ||
		(apple.getLocation().x < m_snake.getHeadLoc().x && !isSafe(otherSnake, right))))
		delta_loc = down;
	else
		delta_loc = prevLoc;

	return delta_loc;
}

void SnakeBot::draw(sf::RenderTarget & target) const
{
	m_snake.draw(target);
}

sf::FloatRect SnakeBot::getGlobalBounds() const
{
	return m_snake.getGlobalBounds();
}

sf::FloatRect SnakeBot::getNextBounds(Snake& otherSnake, Apple& apple)
{
	sf::Vector2f delta_loc = getDeltaLoc(otherSnake, apple);

	return m_snake.getNextBounds(delta_loc);
}

sf::Vector2f SnakeBot::getHeadLoc() const
{
	return m_snake.getHeadLoc();
}

int SnakeBot::getScore() const
{
	return m_snake.getScore();
}

bool SnakeBot::isSafe(const Snake& otherSnake, const sf::Vector2f& delta_loc)
{
	const sf::Vector2f next = m_snake.getNextLoc(delta_loc);

	if (!m_snake.inTileExceptEnd(next) &&
		m_board.insideBoard(next) &&
		!otherSnake.inTileExceptEnd(next))
	{
		return true;
	}
	return false;
}
