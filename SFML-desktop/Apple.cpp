#include "stdafx.h"
#include "Apple.h"
#include <random>

Apple::Apple(Snake& snake, SnakeBot &snakeBot) :
	m_shape(m_board.getDim().x / 2)
{
	m_shape.setFillColor(sf::Color::Red);
	respawn(snake, snakeBot);
}


void Apple::respawn(Snake& snake, SnakeBot &snakeBot)
{
	sf::Vector2f newLoc;
	do
	{
		newLoc.x = float(std::rand() % (int)(m_board.getSize().x - 1));
		newLoc.y = float(std::rand() % (int)(m_board.getSize().y - 1));
	} while (snake.inTile(newLoc) || snakeBot.inTile(newLoc));

	loc = newLoc;

	m_shape.setPosition((loc.x * m_board.getDim().x + m_board.getOffset().x), (loc.y * m_board.getDim().y + m_board.getOffset().y));
}

void Apple::draw(sf::RenderTarget &target) const
{
	target.draw(m_shape);
}

sf::FloatRect Apple::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

sf::Vector2f Apple::getLocation() const
{
	return loc;
}
