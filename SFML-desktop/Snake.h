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
		void follow(const Segment &next);
		void moveBy(const sf::Vector2f &delta_loc);
		const sf::Vector2f &getLocation() const;
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
	void growAndMoveBy(const sf::Vector2f &delta_loc);
	void draw(sf::RenderTarget &target) const;
	void moveBy(const sf::Vector2f &delta_loc);
	bool inTile(const sf::Vector2f &lTarget) const;
	bool inTileExceptEnd(const sf::Vector2f& lTarget) const;
	int getLenght();
	sf::FloatRect getGlobalBounds() const;
	int getScore();
	sf::FloatRect getNextBounds(sf::Vector2f &delta_loc) const;
private:
	Board m_board;
	std::vector<Segment> m_segments;
	std::vector<sf::Color> m_bodyColors;
	void initSnake(int nColors, sf::Color color, ColorInit colorInit, int increment);
	void initColors(ColorInit colorInit, sf::Color &color, int increment, bool &increasing);
	int m_score;
};