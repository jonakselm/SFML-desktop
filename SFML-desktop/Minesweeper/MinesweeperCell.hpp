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

// auto rect = getTextureRect()
// m_sprite.SetTexure()

inline sf::IntRect getTextureRect(CellState cellState, BombState bombState, int surroundingBombs)
{
	if (cellState == CellState::Hidden)
		return sf::IntRect(0, 0, 32, 32);
	else if (cellState == CellState::Flagged)
		return sf::IntRect(32, 0, 32, 32);
	else if (cellState == CellState::WrongFlag)
		return sf::IntRect(64, 32, 32, 32);
	else if (cellState == CellState::Flipped)
	{
		if (bombState == BombState::Bomb)
			return sf::IntRect(32, 32, 32, 32);
		else if (bombState == BombState::Detonated)
			return sf::IntRect(0, 32, 32, 32);
		else if (bombState == BombState::Empty)
		{
			switch (surroundingBombs)
			{
			case 0:
				return sf::IntRect(64, 0, 32, 32);
				break;
			case 1:
				return sf::IntRect(0, 64, 32, 32);
				break;
			case 2:
				return sf::IntRect(32, 64, 32, 32);
				break;
			case 3:
				return sf::IntRect(64, 64, 32, 32);
				break;
			case 4:
				return sf::IntRect(96, 64, 32, 32);
				break;
			case 5:
				return sf::IntRect(0, 96, 32, 32);
				break;
			case 6:
				return sf::IntRect(32, 96, 32, 32);
				break;
			case 7:
				return sf::IntRect(64, 96, 32, 32);
				break;
			case 8:
				return sf::IntRect(96, 96, 32, 32);
				break;
			}
		}
	}
	return sf::IntRect(0, 0, 0, 0);
}

struct MSCell
{
	CellState cellState;
	BombState bombState;
	sf::Sprite cellShape;
};

