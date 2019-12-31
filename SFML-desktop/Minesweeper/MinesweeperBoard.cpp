#include "stdafx.h"
#include "MinesweeperBoard.hpp"

MSBoard::MSBoard(sf::Vector2i dim, int nBombs) :
	m_board(dim.x * dim.y), m_xDim(dim.x), m_yDim(dim.y), m_nBombs(nBombs)
{
	m_texture.loadFromFile("data/images/minesweeperTilemap.png");

	for (int gridX = 0; gridX < m_xDim; ++gridX)
	{
		for (int gridY = 0; gridY < m_yDim; ++gridY)
		{
			auto &cell = getCell(gridX, gridY);
			cell.cellState = CellState::Hidden;

			cell.cellShape.setTexture(m_texture);
			cell.cellShape.setPosition(float(gridX * m_cellDim), float(gridY * m_cellDim));
		}
	}
}

MSCell & MSBoard::getCell(int gridX, int gridY)
{ 
	return m_board[gridX + gridY * m_xDim];
}

void MSBoard::onLeftClick(int coordX, int coordY)
{
	int gridX = coordX / static_cast<int>(m_cellDim);
	int gridY = coordY / static_cast<int>(m_cellDim);
	flip(gridX, gridY);
}

void MSBoard::onRightClick(int coordX, int coordY)
{
	int gridX = coordX / static_cast<int>(m_cellDim);
	int gridY = coordY / static_cast<int>(m_cellDim);
	flag(gridX, gridY);
}

void MSBoard::flip(int gridX, int gridY)
{
	initialize(gridX, gridY);
	MSCell &cell = getCell(gridX, gridY);
	CellState prevCellState = cell.cellState;
	if (prevCellState != CellState::Flipped)
	{
		cell.cellState = CellState::Flipped;
		if (getSurroundingBombs(gridX, gridY) == 0)
		{
			for (int x = gridX - 1; x <= gridX + 1; x++)
			{
				for (int y = gridY - 1; y <= gridY + 1; y++)
				{
					if (x >= 0 && y >= 0 && x < m_xDim && y < m_yDim)
						flip(x, y);
				}
			}
		}
	}
}

void MSBoard::flag(int gridX, int gridY)
{
	initialize(gridX, gridY);
	MSCell &cell = getCell(gridX, gridY);
	CellState prevCellState = cell.cellState;
	if (prevCellState != CellState::Flipped)
	{
		if (prevCellState == CellState::Hidden)
			cell.cellState = CellState::Flagged;
		else if (prevCellState == CellState::Flagged)
			cell.cellState = CellState::Hidden;
	}
}

void MSBoard::initialize(int gridStartX, int gridStartY)
{
	if (!m_initialized)
	{
		int nSpawned = 0;
		while (nSpawned < m_nBombs)
		{
			int x = std::rand() % m_xDim;
			int y = std::rand() % m_yDim;
			MSCell &cell = getCell(x, y);
			BombState cellPrevState = cell.bombState;
			if (cellPrevState != BombState::Bomb && &cell != &getCell(gridStartX, gridStartY))
			{
				cell.bombState = BombState::Bomb;
				nSpawned++;
			}
		}
		m_initialized = true;
	}
}

void MSBoard::draw(sf::RenderTarget &target)
{
	for (int gridX = 0; gridX < m_xDim; ++gridX)
	{
		for (int gridY = 0; gridY < m_yDim; ++gridY)
		{
			auto &cell = getCell(gridX, gridY);
			int surroundingBombs = getSurroundingBombs(gridX, gridY);
			auto textureRect = getTextureRect(cell.cellState, cell.bombState, surroundingBombs);
			cell.cellShape.setTextureRect(textureRect);
			cell.cellShape.setScale(m_cellDim / m_textureDim, m_cellDim / m_textureDim);
			target.draw(cell.cellShape);
		}
	}
}

int MSBoard::getSurroundingBombs(int gridX, int gridY)
{
	int nBombs = 0;
	for (int x = gridX - 1; x <= gridX + 1; x++)
	{
		for (int y = gridY - 1; y <= gridY + 1; y++)
		{
			if (x >= 0 && y >= 0 && x < m_xDim && y < m_yDim)
			{
				MSCell &cell = getCell(x, y);
				if (cell.bombState == BombState::Bomb)
					nBombs++;
			}
		}
	}

	return nBombs;
}
