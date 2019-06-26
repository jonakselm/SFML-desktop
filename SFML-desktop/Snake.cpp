#include "stdafx.h"
#include "Snake.h"

Snake::Snake(const sf::Vector2f & loc, int nColors, sf::Color startColor, ColorInit colorInit, int increment)
{
	// Use even numbers for nBodyColors for smooth color transition
	initColors(nColors, startColor, colorInit, increment);
	segments.emplace_back(loc);
}

sf::Vector2f Snake::nextHeadLoc(const sf::Vector2f & delta_loc) const
{
	sf::Vector2f l(segments[0].GetLocation());
	l += delta_loc;
	return l;
}

void Snake::GrowAndMoveBy(const sf::Vector2f &delta_loc)
{
	segments.emplace_back(bodyColors[segments.size() % bodyColors.size()]);

	MoveBy(delta_loc);

	score++;
}

Snake::Segment::Segment(const sf::Vector2f & in_loc)
	:
	body(board.getDim())
{
	loc = in_loc;
	body.setFillColor(sf::Color(100, 255, 0));
	body.setOutlineThickness(-1.5);
	body.setOutlineColor(sf::Color::Black);
	body.setPosition(loc.x * board.getDim() + board.getOffset());
}

Snake::Segment::Segment(sf::Color c_in)
	:
	body(board.getDim())
{
	c = c_in;
	body.setOutlineThickness(-1.5);
	body.setOutlineColor(sf::Color::Black);
	body.setFillColor(c);
}

void Snake::Segment::draw(sf::RenderTarget &target) const
{
	target.draw(body);
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
	body.setPosition(next.GetLocation().x * board.getDim().x + board.getOffset().x, next.GetLocation().y * board.getDim().y + board.getOffset().y);
}

void Snake::Segment::MoveBy(const sf::Vector2f & delta_loc)
{
	loc += delta_loc;

	sf::Vector2f delta(delta_loc.x * board.getDim().x, delta_loc.y * board.getDim().y);
	auto prev = body.getPosition();
	body.setPosition(sf::Vector2f(prev + delta));
}

const sf::Vector2f & Snake::Segment::GetLocation() const
{
	return loc;
}

sf::FloatRect Snake::Segment::getGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Snake::draw(sf::RenderTarget &target) const
{
	for (auto it = segments.rbegin(); it != segments.rend(); ++it)
	{
		it->draw(target);
	}
}

void Snake::MoveBy(const sf::Vector2f & delta_loc)
{
	for (size_t i = segments.size() - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments.front().MoveBy(delta_loc);
}

bool Snake::inTile(const sf::Vector2f & lTarget) const
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

bool Snake::inTileExceptEnd(const sf::Vector2f & lTarget) const
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
	return static_cast<int>(segments.size());
}

sf::FloatRect Snake::getGlobalBounds() const
{
	return segments.front().getGlobalBounds();
}

int Snake::GetScore()
{
	return score;
}

sf::FloatRect Snake::getNextBounds(sf::Vector2f &delta_loc) const
{
	sf::Vector2f l(segments[0].GetLocation());
	l += delta_loc;
	sf::FloatRect currPos = segments.front().getGlobalBounds();
	sf::Vector2f nextPos = { currPos.left + delta_loc.x * board.getDim().x, currPos.top + delta_loc.y * board.getDim().y };
	return sf::FloatRect(nextPos, board.getDim());
}

void Snake::initColors(int nColors, sf::Color color, ColorInit colorInit, int increment)
{
	bodyColors.reserve(nColors);

	bool increase = false, decrease = true;

	int limit = 25;

	switch (colorInit)
	{
	case ColorInit::Red:
	{
		for (int i = 0; i < nColors; i++)
		{
			if ((color.r - increment) > limit)
			{
				if ((color.r - increment) < limit)
				{
					color.r = increment + limit;
				}
				color.r -= increment;
				bodyColors.push_back(color);
			}
			else if ((color.r + increment) < 255)
			{
				if ((color.r + increment) > 255)
				{
					color.r = 255 - limit - increment;
				}
				color.r += increment;
				bodyColors.push_back(color);
			}
		}
	}
		break;
	case ColorInit::Green:
	{
		for (int i = 0; i < nColors; i++)
		{
			if ((color.g - increment) > limit)
			{
				if ((color.g - increment) < limit)
				{
					color.g = increment + limit;
				}
				color.g -= increment;
				bodyColors.push_back(color);
			}
			else if ((color.g + increment) < 255)
			{
				if ((color.g + increment) > 255)
				{
					color.g = 255 - limit - increment;
				}
				color.g += increment;
				bodyColors.push_back(color);
			}
		}
	}
	break;
	case ColorInit::Blue:
	{
		for (int i = 0; i < nColors; i++)
		{
			if ((color.b - increment) > limit)
			{
				if ((color.b - increment) < limit)
				{
					color.b = increment + limit;
				}
				color.b -= increment;
				bodyColors.push_back(color);
			}
			else if ((color.b + increment) < 255)
			{
				if ((color.b + increment) > 255)
				{
					color.b = 255 - limit - increment;
				}
				color.b += increment;
				bodyColors.push_back(color);
			}
		}
	}
	break;
	case ColorInit::All:
	{
	}
	break;
	}
}

