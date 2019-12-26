#include "stdafx.h"
#include "SnakeBoard.h"

SnakeBoard::SnakeBoard()
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

void SnakeBoard::drawBoard(sf::RenderTarget & target) const
{
	target.draw(top);
	target.draw(bottom);
	target.draw(left);
	target.draw(right);
}

bool SnakeBoard::insideBoard(const sf::FloatRect &target)
{
	return target.left >= left.getPosition().x + left.getSize().x &&
		target.top >= top.getPosition().y + top.getSize().y &&
		target.left + target.width <= right.getGlobalBounds().left &&
		target.top + target.height <= bottom.getGlobalBounds().top;
}

sf::Vector2f SnakeBoard::getDim() const
{
	return dim;
}

sf::Vector2f SnakeBoard::getOffset() const
{
	return offset;
}

sf::Vector2f SnakeBoard::getSize() const
{
	return size;
}
