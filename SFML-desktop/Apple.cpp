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
	sf::FloatRect newBounds;
	do
	{
		sf::Vector2f newPos;
		newPos.x = float(std::rand() % (int)(m_board.getSize().x - 1));
		newPos.y = float(std::rand() % (int)(m_board.getSize().y - 1));

		newPos.x *= m_board.getDim().x;
		newPos.y *= m_board.getDim().y;

		newPos += m_board.getOffset();

		newBounds = sf::FloatRect(newPos, sf::Vector2f(m_board.getDim()));
	} while (snake.inTile(newBounds) || snakeBot.inTile(newBounds));

	bounds = newBounds;

	m_shape.setPosition(bounds.left, bounds.top);
}

void Apple::draw(sf::RenderTarget &target) const
{
	target.draw(m_shape);
}

sf::FloatRect Apple::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}
