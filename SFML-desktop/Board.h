#pragma once

#include "Location.h"

class Board
{
public:
	Board();

	void drawBoard(sf::RenderTarget &target) const;

	bool InsideBoard(const sf::Vector2f &loc);

	sf::Vector2f getDim() const;
	sf::Vector2f getOffset() const;
	sf::Vector2f getSize() const;
private:
	const sf::Vector2f offset = { 100, 50 };
	const sf::Vector2f dim = { 15, 15 };
	const sf::Vector2f circleDim = { dim.x / 2, 10 };
	const sf::Vector2f size = { 50, 50 };

	sf::RectangleShape top, bottom, left, right;
};