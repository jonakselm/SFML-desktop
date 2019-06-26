#pragma once

#include "Shape.hpp"
#include <vector>
#include "Board.h"

enum class ColorInit { Red, Green, Blue, All };

class Snake : public Shape
{
private:
	class Segment : public Shape
	{
	public:
		Segment(const sf::Vector2f &in_loc);
		Segment(sf::Color c_in);
		void draw(sf::RenderTarget &target) const;
		void Follow(const Segment &next);
		void MoveBy(const sf::Vector2f &delta_loc);
		const sf::Vector2f &GetLocation() const;
		sf::FloatRect getGlobalBounds() const;
	private:
		Board board;
		sf::RectangleShape body;
		sf::Vector2f loc;
		sf::Color c;
	};
public:
	Snake(const sf::Vector2f &loc, int nColors, sf::Color startColor, ColorInit colorInit, int increment);
	sf::Vector2f nextHeadLoc(const sf::Vector2f& delta_loc) const;
	void GrowAndMoveBy(const sf::Vector2f &delta_loc);
	void draw(sf::RenderTarget &target) const;
	void MoveBy(const sf::Vector2f &delta_loc);
	bool inTile(const sf::Vector2f &lTarget) const;
	bool inTileExceptEnd(const sf::Vector2f& lTarget) const;
	int GetLenght();
	sf::FloatRect getGlobalBounds() const;
	int GetScore();
	sf::FloatRect getNextBounds(sf::Vector2f &delta_loc) const;
private:
	Board board;
	std::vector<Segment> segments;
	std::vector<sf::Color>bodyColors;
	void initColors(int nColors, sf::Color color, ColorInit colorInit, int increment);
	int score;
};