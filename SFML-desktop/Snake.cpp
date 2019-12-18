#include "stdafx.h"
#include "Snake.h"

Snake::Snake(const sf::Vector2f & loc, int nColors, const sf::Color &startColor, const ColorInit colorInit, int increment)
{
	// Use even numbers for nBodyColors for smooth color transition
	initSnake(nColors, startColor, colorInit, increment);
	m_segments.emplace_back(loc);
}

sf::Vector2f Snake::getNextLoc(const sf::Vector2f & delta_loc) const
{
	sf::Vector2f nextLoc = m_headLoc + delta_loc;
	return nextLoc;
}

void Snake::growAndMoveBy(const sf::Vector2f &delta_loc)
{
	m_segments.emplace_back(m_bodyColors[m_segments.size() % m_bodyColors.size()]);

	moveBy(delta_loc);
}

Snake::Segment::Segment(const sf::Vector2f & in_loc)
	:
	m_body(m_board.getDim())
{
	m_body.setFillColor(sf::Color(100, 255, 0));
	m_body.setOutlineThickness(-1.5);
	m_body.setOutlineColor(sf::Color::Black);
	sf::Vector2f loc = sf::Vector2f(in_loc.x * m_board.getDim().x + m_board.getOffset().x, in_loc.y * m_board.getDim().y + m_board.getOffset().y);
	m_body.setPosition(loc);
}

Snake::Segment::Segment(sf::Color c_in)
	:
	m_body(m_board.getDim())
{
	m_color = c_in;
	m_body.setOutlineThickness(-1.5);
	m_body.setOutlineColor(sf::Color::Black);
	m_body.setFillColor(m_color);
}

void Snake::Segment::draw(sf::RenderTarget &target) const
{
	target.draw(m_body);
}

void Snake::Segment::follow(const Segment & next)
{
	m_body.setPosition(next.getPosition().x, next.getPosition().y);
}

void Snake::Segment::moveBy(const sf::Vector2f & delta_loc)
{
	m_body.move(delta_loc);
}

void Snake::Segment::setColor(const sf::Color & color)
{
	m_color = color;
	m_body.setFillColor(color);
}

sf::FloatRect Snake::Segment::getGlobalBounds() const
{
	return m_body.getGlobalBounds();
}

sf::Vector2f Snake::Segment::getPosition() const
{
	return m_body.getPosition();
}

void Snake::draw(sf::RenderTarget &target) const
{
	for (auto it = m_segments.rbegin(); it != m_segments.rend(); ++it)
	{
		it->draw(target);
	}
}

void Snake::moveBy(const sf::Vector2f & delta_loc)
{
	sf::Vector2f delta = delta_loc;

	delta.x *= m_board.getDim().x;
	delta.y *= m_board.getDim().y;

	for (size_t i = m_segments.size() - 1; i > 0; i--)
	{
		m_segments[i].follow(m_segments[i - 1]);
	}
	m_segments.front().moveBy(delta);

	m_headLoc += delta_loc;
}

void Snake::setHeadColor(const sf::Color & headColor)
{
	m_segments.front().setColor(headColor);
}

void Snake::setDead()
{
	dead = true;
}

bool Snake::inTile(const sf::FloatRect &targetRect) const
{
	// Checks if the target is in the same location as any of the segments
	for (const auto s : m_segments)
	{
		if (s.getGlobalBounds().intersects(targetRect))
		{
			return true;
		}
	}
	return false;
}

bool Snake::inTileExceptEnd(const sf::FloatRect &targetRect) const
{
	// Checks if the target is in the same location as any of the segments except the end segment
	for (size_t i = 0; i < m_segments.size() - 1; i++)
	{
		if (m_segments[i].getGlobalBounds().intersects(targetRect))
		{
			return true;
		}
	}
	return false;
}

bool Snake::isDead() const
{
	return dead;
}

int Snake::getLength() const
{
	return static_cast<int>(m_segments.size());
}

int Snake::getScore() const
{
	return getLength() - 1;
}

sf::FloatRect Snake::getGlobalBounds() const
{
	return m_segments.front().getGlobalBounds();
}

sf::FloatRect Snake::getNextBounds(sf::Vector2f &delta_loc) const
{
	sf::Vector2f loc = m_headLoc;
	loc += delta_loc;
	sf::Vector2f currPos = m_segments.front().getPosition();
	sf::Vector2f nextPos = { currPos.x + delta_loc.x * m_board.getDim().x, currPos.y + delta_loc.y * m_board.getDim().y };
	return sf::FloatRect(nextPos, m_board.getDim());
}

sf::Vector2f Snake::getHeadLoc() const
{
	return m_headLoc;
}

void Snake::initSnake(int nColors, sf::Color color, ColorInit colorInit, int increment)
{
	m_bodyColors.reserve(nColors);

	bool rIncreasing = false, gIncreasing = false, bIncreasing = false, increasing = false;

	switch (colorInit)
	{
	case ColorInit::Red:
	case ColorInit::Green:
	case ColorInit::Blue:
		for (int i = 0; i < nColors; i++)
		{
			initColors(colorInit, color, increment, increasing);
			m_bodyColors.push_back(color);
		}
		break;
	case ColorInit::All:
		for (int i = 0; i < nColors; i++)
		{
			initColors(ColorInit::Red, color, increment, rIncreasing);
			initColors(ColorInit::Green, color, increment, gIncreasing);
			initColors(ColorInit::Blue, color, increment, bIncreasing);
			m_bodyColors.push_back(color);
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

	if (tempColor - increment < 25)
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

