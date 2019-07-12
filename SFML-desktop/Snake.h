#pragma once

#include "Shape.hpp"
#include <vector>
#include "Board.h"

class Snake : public Shape
{
public:
	enum class ColorInit { Red, Green, Blue, All };
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
		Board m_board;
		sf::RectangleShape m_body;
		sf::Vector2f m_loc;
		sf::Color m_c;
	};
public:
	Snake(const sf::Vector2f &loc, int nColors, sf::Color startColor, ColorInit colorInit, int increment);
	sf::Vector2f getNextLoc(const sf::Vector2f& delta_loc) const;
	sf::Vector2f getHeadLoc() const;
	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getNextBounds(sf::Vector2f &delta_loc) const;
	void growAndMoveBy(const sf::Vector2f &delta_loc);
	void moveBy(const sf::Vector2f &delta_loc);
	bool inTile(const sf::Vector2f &lTarget) const;
	bool inTileExceptEnd(const sf::Vector2f& lTarget) const;
	int getLength() const;
	int getScore() const;
	void draw(sf::RenderTarget &target) const;

private:
	void initSnake(int nColors, sf::Color color, ColorInit colorInit, int increment);
	void initColors(ColorInit colorInit, sf::Color &color, int increment, bool &increasing);

private:
	Board m_board;
	std::vector<Segment> m_segments;
	std::vector<sf::Color> m_bodyColors;
};