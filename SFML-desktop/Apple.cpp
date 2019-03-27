#include "stdafx.h"
#include "Apple.h"
#include <random>

Apple::Apple() :
	m_shape(board.getDim().x / 2)
{
	m_shape.setFillColor(sf::Color::Red);
	respawn();
}


void Apple::respawn()
{
	sf::Vector2f newLoc;
	newLoc.x = float(std::rand() % (int)(board.getSize().x - 1));
	newLoc.y = float(std::rand() % (int)(board.getSize().y - 1));
	m_shape.setPosition((newLoc.x * board.getDim().x + board.getOffset().x), (newLoc.y * board.getDim().y + board.getOffset().y));
}

void Apple::draw(sf::RenderTarget &target) const
{
	target.draw(m_shape);
}

sf::FloatRect Apple::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}
