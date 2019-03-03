#include "stdafx.h"
#include "Apple.h"
#include "Board.h"
#include <random>

Apple::Apple() :
	m_shape(15.f)
{
	m_shape.setFillColor(sf::Color::Red);
	respawn();
}


void Apple::respawn()
{
	Location newLoc;
	newLoc.x = float(std::rand() % (Board::width - 1));
	newLoc.y = float(std::rand() % (Board::height - 1));
	m_shape.setPosition((newLoc.x * Board::dim), (newLoc.y * Board::dim));
}

void Apple::draw(sf::RenderTarget &target) const
{
	target.draw(m_shape);
}

sf::FloatRect Apple::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}
