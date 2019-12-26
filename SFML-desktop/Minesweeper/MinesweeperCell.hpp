#pragma once

enum class CellState
{
	Hidden,
	Flagged,
	Flipped,
};

enum class BombState
{
	Empty,
	Bomb
};

// auto rect = getTextureRect()
// m_sprite.SetTexure()

inline sf::IntRect getTextureRect(CellState cellstate, BombState bombState)
{
	// if (CellState == CellState::Hidden)
	//    return sf::IntRect(0,0,32,32);
	return sf::IntRect(0, 0, 0, 0);
}

struct MSCell
{
	CellState cellState;
	BombState bombState;
	sf::Sprite cellShape;
};

