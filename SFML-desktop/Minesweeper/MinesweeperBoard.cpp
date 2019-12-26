#include "stdafx.h"
#include "MinesweeperBoard.hpp"

MSBoard::MSBoard(unsigned int xDim, unsigned int yDim) : 
	m_board(xDim * yDim), m_xDim(xDim), m_yDim(yDim)
{
	//m_texture.load

	for (unsigned x = 0; x < m_xDim; ++x)
	{
		for (unsigned y = 0; y < m_yDim; ++y)
		{
			auto &cell = getCell(x, y);
			cell.cellState = CellState::Hidden;

			if (std::rand() % 10)
				cell.bombState = BombState::Empty;
			else
				cell.bombState = BombState::Bomb;

			cell.cellShape.setTexture(m_texture);
		}
	}
}

MSCell & MSBoard::getCell(unsigned int x, unsigned int y)
{ 
	return m_board[x + y * m_xDim]; 
}

void MSBoard::draw(sf::RenderTarget &target)
{
	for (unsigned x = 0; x < m_xDim; ++x)
	{
		for (unsigned y = 0; y < m_yDim; ++y)
		{
			auto &cell = getCell(x, y);
			auto textureRect = getTextureRect(cell.cellState, cell.bombState);
			cell.cellShape.setTextureRect(textureRect);
		}
	}
}
