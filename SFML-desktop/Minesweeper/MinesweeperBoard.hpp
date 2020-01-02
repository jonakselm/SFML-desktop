#pragma once
#include "MinesweeperCell.hpp"

class MSBoard
{
public:
	MSBoard(sf::Vector2i dim, int nBombs);

	MSCell &getCell(int gridX, int gridY);

	void onLeftClick(int coordX, int coordY);
	void onRightClick(int coordX, int coordY);
	void flip(int gridX, int gridY);
	void flag(int gridX, int gridY);
	void revealBombs();
	void revealHiddenCells();
	void revealWrongFlags();
	bool checkForWin();

	bool isGameOver() const;
	bool isGameWon() const;
	float getCellDim() const;

	void initialize(int gridStartX, int gridStartY);
	void draw(sf::RenderTarget &target);
	int getSurroundingBombs(int gridX, int gridY);

private:
	int m_xDim, m_yDim;
	std::vector<MSCell> m_board;
	sf::Texture m_texture;

	const int m_nBombs;
	bool m_initialized = false, m_gameOver = false, m_gameWon = false;
	const float m_cellDim = 64, m_textureDim = 32;
};