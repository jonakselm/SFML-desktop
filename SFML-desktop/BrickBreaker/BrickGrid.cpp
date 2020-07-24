#include "stdafx.h"
#include "BrickGrid.hpp"

BrickGrid::BrickGrid(int gridWidth, int gridHeight)
	:
	m_gridSize(sf::Vector2f(gridWidth, gridHeight))
{
	const auto predefColors = std::array
	{
		sf::Color(255, 0, 0),
		sf::Color(225, 0, 0),
		sf::Color(200, 0, 0),
		sf::Color(175, 0, 0),
		sf::Color(150, 0, 0),
		sf::Color(125, 0, 0),
		sf::Color(100, 0, 0),
		sf::Color(0, 255, 0),
		sf::Color(0, 225, 0),
		sf::Color(0, 200, 0),
		sf::Color(0, 175, 0),
		sf::Color(0, 150, 0),
		sf::Color(0, 125, 0),
		sf::Color(0, 100, 0),
		sf::Color(0, 0, 255),
		sf::Color(0, 0, 225),
		sf::Color(0, 0, 200),
		sf::Color(0, 0, 175),
		sf::Color(0, 0, 150),
		sf::Color(0, 0, 125),
		sf::Color(0, 0, 100)
		/*sf::Color(255, 0, 0),
		sf::Color(0, 255, 0),
		sf::Color(0, 0, 255),
		sf::Color(255, 255, 0),
		sf::Color(255, 0, 255),
		sf::Color(0, 255, 255),
		sf::Color(128, 128, 128)*/
	};

	m_bricks.reserve(gridWidth * gridHeight);

	for (std::size_t y = 0; y < gridHeight; y++)
	{
		for (std::size_t x = 0; x < gridWidth; x++)
		{
			Brick &newBrick = m_bricks.emplace_back();
			newBrick.shape.setPosition(x * m_brickSize.x, y * m_brickSize.y);
			newBrick.shape.setSize(m_brickSize);
			newBrick.shape.setOutlineThickness(-1);
			newBrick.shape.setOutlineColor(sf::Color::Black);

			newBrick.shape.setFillColor(predefColors[(y * gridWidth + x) % predefColors.size()]);
		}
	}
}

BrickGrid::~BrickGrid()
{
}

sf::Vector2f BrickGrid::getGridSize() const
{
	return m_gridSize;
}

const Brick &BrickGrid::getBrick(int x, int y) const
{
	return m_bricks[x + y * m_gridSize.x];
}

Brick &BrickGrid::getBrick(int x, int y)
{
	return m_bricks[x + y * m_gridSize.x];
}

void BrickGrid::popBrick(int x, int y)
{
	Brick &brick = getBrick(x, y);
	brick.destroyed = true;
}

void BrickGrid::draw(sf::RenderTarget &target)
{
	for (const auto &brick : m_bricks)
		if (!brick.destroyed)
			target.draw(brick.shape);
}
