#pragma once

#include "../Shape.hpp"
#include "SnakeBoard.h"

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
		void setColor(const sf::Color &color);

		sf::FloatRect getGlobalBounds() const;
		sf::Vector2f getPosition() const;

	private:
		SnakeBoard m_board;
		sf::RectangleShape m_body;
		sf::Color m_color;
	};
public:
	Snake(const sf::Vector2f & loc, int nColors, const sf::Color &startColor, const ColorInit colorInit, int increment);

	sf::Vector2f getNextLoc(const sf::Vector2f& delta_loc) const;
	sf::Vector2f getHeadLoc() const;
	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getNextBounds(sf::Vector2f &delta_loc) const;

	void growAndMoveBy(const sf::Vector2f &delta_loc);
	void moveBy(const sf::Vector2f &delta_loc);
	void setHeadColor(const sf::Color &headColor);
	void setDead();

	bool inTile(const sf::FloatRect &targetRect) const;
	bool inTileExceptEnd(const sf::FloatRect &targetRect) const;
	bool isDead() const;

	int getLength() const;
	int getScore() const;

	void draw(sf::RenderTarget &target) const;

private:
	void initSnake(int nColors, sf::Color color, ColorInit colorInit, int increment);
	void initColors(ColorInit colorInit, sf::Color &color, int increment, bool &increasing);

private:
	SnakeBoard m_board;
	std::vector<Segment> m_segments;
	std::vector<sf::Color> m_bodyColors;
	sf::Vector2f m_headLoc;
	bool dead = false;
};