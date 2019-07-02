#include "stdafx.h"
#include "Snake.h"

Snake::Snake(const sf::Vector2f & loc, int nColors, sf::Color startColor, ColorInit colorInit, int increment)
{
	// Use even numbers for nBodyColors for smooth color transition
	initSnake(nColors, startColor, colorInit, increment);
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

void Snake::initSnake(int nColors, sf::Color color, ColorInit colorInit, int increment)
{
	bodyColors.reserve(nColors);

	bool rIncreasing = false, gIncreasing = false, bIncreasing = false, increasing = false;

	switch (colorInit)
	{
	case ColorInit::Red:
	case ColorInit::Green:
	case ColorInit::Blue:
		for (int i = 0; i < nColors; i++)
		{
			initColors(colorInit, color, increment, increasing);
			bodyColors.push_back(color);
		}
		break;
	case ColorInit::All:
		for (int i = 0; i < nColors; i++)
		{
			initColors(ColorInit::Red, color, increment, rIncreasing);
			initColors(ColorInit::Green, color, increment, gIncreasing);
			initColors(ColorInit::Blue, color, increment, bIncreasing);
			bodyColors.push_back(color);
		}
		break;
	}
}

void Snake::initColors(ColorInit colorInit, sf::Color &color, int increment, bool &increasing)
{
	sf::Uint8 tempColor;

	switch (colorInit)
	{
	case ColorInit::Red:
		tempColor = color.r;
		break;
	case ColorInit::Green:
		tempColor = color.g;
		break;
	case ColorInit::Blue:
		tempColor = color.b;
		break;
	}

	if (tempColor - increment < 10)
	{
		increasing = true;
	}
	else if (tempColor + increment > 255)
	{
		increasing = false;
	}

	if (increasing)
	{
		tempColor += increment;
	}
	else
	{
		tempColor -= increment;
	}

	switch (colorInit)
	{
	case ColorInit::Red:
		color.r = tempColor;
		break;
	case ColorInit::Green:
		color.g = tempColor;
		break;
	case ColorInit::Blue:
		color.b = tempColor;
		break;
	}
}

