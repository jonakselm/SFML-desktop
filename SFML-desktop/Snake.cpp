#include "stdafx.h"
#include "Snake.h"

Snake::Snake(const Location & loc)
{
	segments.emplace_back(loc);
}

Location Snake::nextHeadLoc(const Location & delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::GrowAndMoveBy(const Location &delta_loc)
{
	segments.emplace_back(bodyColor);

	MoveBy(delta_loc);

	score++;
}

Snake::Segment::Segment(const Location & in_loc)
{
	loc = in_loc;
	c = sf::Color::Green;
}

Snake::Segment::Segment(sf::Color c_in)
{
	c = c_in;
}

void Snake::Segment::draw(sf::RenderTarget &target) const
{
	Board::drawRect(loc, c, target);
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	loc.Add(delta_loc);
}

const Location & Snake::Segment::GetLocation() const
{
	return loc;
}

sf::FloatRect Snake::Segment::getGlobalBounds() const
{
	return sf::FloatRect(loc.x * Board::dim, loc.y * Board::dim, Board::dim, Board::dim);
}

void Snake::draw(sf::RenderTarget &target) const
{
	for (auto it = segments.rbegin(); it != segments.rend(); ++it)
	{
		it->draw(target);
	}
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (size_t i = segments.size() - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments.front().MoveBy(delta_loc);
}

bool Snake::inTile(const Location & lTarget) const
{
	for (const auto s : segments)
	{
		if (s.GetLocation() == lTarget)
		{
			return true;
		}
	}
	return false;
}

bool Snake::inTileExceptEnd(const Location & lTarget) const
{
	for (size_t i = 0; i < segments.size() - 1; i++)
	{
		if (segments[i].GetLocation() == lTarget)
		{
			return true;
		}
	}
	return false;
}

int Snake::GetLenght()
{
	return (int)segments.size();
}

sf::FloatRect Snake::getGlobalBounds() const
{
	return segments.front().getGlobalBounds();
}

int Snake::GetScore()
{
	return score;
}

sf::FloatRect Snake::getNextBounds(Location &delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return sf::FloatRect(l.x * Board::dim, l.y * Board::dim, Board::dim, Board::dim);
}

