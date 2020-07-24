#pragma once

enum class CellState
{
	Hidden,
	Flagged,
	Flipped,
	WrongFlag
};

enum class BombState
{
	Empty,
	Bomb,
	Detonated
};

struct MSCell
{
	CellState cellState;
	BombState bombState;
	sf::Sprite cellShape;
	const int textureDim = 16;
};

inline sf::IntRect getTextureRect(CellState cellState, BombState bombState, int surroundingBombs)
{
	MSCell cell;

	if (cellState == CellState::Hidden)
		return sf::IntRect(0, 0, cell.textureDim, cell.textureDim);
	else if (cellState == CellState::Flagged)
		return sf::IntRect(cell.textureDim, 0, cell.textureDim, cell.textureDim);
	else if (cellState == CellState::WrongFlag)
		return sf::IntRect(cell.textureDim * 2, cell.textureDim, cell.textureDim, cell.textureDim);
	else if (cellState == CellState::Flipped)
	{
		if (bombState == BombState::Bomb)
			return sf::IntRect(0, cell.textureDim, cell.textureDim, cell.textureDim);
		else if (bombState == BombState::Detonated)
			return sf::IntRect(cell.textureDim, cell.textureDim, cell.textureDim, cell.textureDim);
		else if (bombState == BombState::Empty)
		{
			switch (surroundingBombs)
			{
			case 0:
				return sf::IntRect(cell.textureDim * 2, 0, cell.textureDim, cell.textureDim);
				break;
			case 1:
				return sf::IntRect(0, cell.textureDim * 2, cell.textureDim, cell.textureDim);
				break;
			case 2:
				return sf::IntRect(cell.textureDim, cell.textureDim * 2, cell.textureDim, cell.textureDim);
				break;
			case 3:
				return sf::IntRect(cell.textureDim * 2, cell.textureDim * 2, cell.textureDim, cell.textureDim);
				break;
			case 4:
				return sf::IntRect(cell.textureDim * 3, cell.textureDim * 2, cell.textureDim, cell.textureDim);
				break;
			case 5:
				return sf::IntRect(0, cell.textureDim * 3, cell.textureDim, cell.textureDim);
				break;
			case 6:
				return sf::IntRect(cell.textureDim, cell.textureDim * 3, cell.textureDim, cell.textureDim);
				break;
			case 7:
				return sf::IntRect(cell.textureDim * 2, cell.textureDim * 3, cell.textureDim, cell.textureDim);
				break;
			case 8:
				return sf::IntRect(cell.textureDim * 3, cell.textureDim * 3, cell.textureDim, cell.textureDim);
				break;
			}
		}
	}
	return sf::IntRect(0, 0, 0, 0);
}

