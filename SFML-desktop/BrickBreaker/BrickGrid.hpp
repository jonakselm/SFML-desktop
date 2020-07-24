#pragma once
#include "Brick.hpp"

class BrickGrid
{
public:
	BrickGrid(int gridWidth, int gridHeight);
	~BrickGrid();

	sf::Vector2f getGridSize() const;

	const Brick &getBrick(int x, int y) const;
	Brick &getBrick(int x, int y);

	void popBrick(int x, int y);

	void draw(sf::RenderTarget &target);

private:
	std::vector<Brick> m_bricks;
	std::vector<sf::Color> m_rowColors;
	const sf::Vector2f m_gridSize;
	const sf::Vector2f m_brickSize = { 60, 30 };
};