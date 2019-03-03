#pragma once

#include "Board.h"
#include <vector>
#include "Shape.hpp"

class Snake : public Shape
{
private:
	class Segment : public Shape
	{
	public:
		Segment(const Location &in_loc);
		Segment(sf::Color c_in);
		void draw(sf::RenderTarget &target) const;
		void Follow(const Segment &next);
		void MoveBy(const Location &delta_loc);
		const Location &GetLocation() const;
		sf::FloatRect getGlobalBounds() const;
	private:
		Location loc;
		sf::Color c;
	};
public:
	Snake(const Location &loc);
	Location nextHeadLoc(const Location& delta_loc) const;
	void GrowAndMoveBy(const Location &delta_loc);
	void draw(sf::RenderTarget &target) const;
	void MoveBy(const Location &delta_loc);
	bool inTile(const Location &lTarget) const;
	bool inTileExceptEnd(const Location& lTarget) const;
	int GetLenght();
	sf::FloatRect getGlobalBounds() const;
	int GetScore();
	sf::FloatRect getNextBounds(Location &delta_loc) const;
private:
	sf::Color bodyColor = sf::Color::Magenta;
	std::vector<Segment> segments;
	int score;
};