#include "stdafx.h"
#include "Board.h"

void Board::drawRect(const Location & loc, sf::Color c, sf::RenderTarget & target)
{
	sf::RectangleShape shape(sf::Vector2f(dim, dim));
	shape.setFillColor(c);
	shape.setPosition(loc.x * dim, loc.y * dim);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(-1.5);
	target.draw(shape);
}

void Board::drawCircle(const Location & loc, sf::Color c, sf::RenderTarget & target)
{
	sf::CircleShape shape(dim / 2);
	shape.setFillColor(c);
	shape.setPosition(loc.x * dim, loc.y * dim);
	target.draw(shape);
}

bool Board::InsideBoard(const Location &loc)
{
	return loc.x >= 0 && loc.y >= 0 &&
		loc.x <= (width - 1) && loc.y <= (height - 1);
}
