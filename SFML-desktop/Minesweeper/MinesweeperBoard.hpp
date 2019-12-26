#pragma once
#include "MinesweeperCell.hpp"

class MSBoard
{
public:
	MSBoard(unsigned int xDim, unsigned int yDim);

	MSCell &getCell(unsigned int x, unsigned int y);

	void draw(sf::RenderTarget &target);

private:
	unsigned int m_xDim, m_yDim;
	std::vector<MSCell> m_board;
	sf::Texture m_texture;
};