#include "stdafx.h"
#include "Board.h"

Board::Board()
	:
	top(sf::Vector2f(dim.x * size.x, dim.y / 2)),
	bottom(sf::Vector2f(dim.x * size.x, dim.y / 2)),
	left(sf::Vector2f(dim.x / 2, dim.y * size.y + dim.y)),
	right(sf::Vector2f(dim.x / 2, dim.y * size.y + dim.y))
{
	top.setPosition(offset.x, offset.y - dim.y + dim.y / 2);
	bottom.setPosition(offset.x, offset.y + size.y * dim.y);
	left.setPosition(offset.x - dim.x + dim.x / 2, offset.y - dim.y / 2);
	right.setPosition(offset.x + size.x * dim.x, offset.y - dim.y / 2);
}

void Board::drawBoard(sf::RenderTarget & target) const
{
	target.draw(top);
	target.draw(bottom);
	target.draw(left);
	target.draw(right);
}

bool Board::insideBoard(const sf::Vector2f &loc)
{
	return loc.x >= 0 && loc.y >= 0 &&
		loc.x <= (size.x - 1) && loc.y <= (size.y - 1);
}

sf::Vector2f Board::getDim() const
{
	return dim;
}

sf::Vector2f Board::getOffset() const
{
	return offset;
}

sf::Vector2f Board::getSize() const
{
	return size;
}
