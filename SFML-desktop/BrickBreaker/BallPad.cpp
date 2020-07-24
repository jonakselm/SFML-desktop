#include "stdafx.h"
#include "BallPad.hpp"

BallPad::BallPad()
	:
	m_shape(sf::Vector2f(120, 20))
{
	m_shape.setFillColor(sf::Color::Cyan);
	m_shape.setPosition(425, 750);
}

BallPad::~BallPad()
{
}

float BallPad::getPadSpeed()
{
	return s_padSpeed;
}

sf::Vector2f BallPad::getPosition()
{
	return m_shape.getPosition();
}

sf::Vector2f BallPad::getCenterPos()
{
	return m_shape.getPosition() + sf::Vector2f(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
}

sf::Vector2f BallPad::getSize()
{
	return m_shape.getSize();
}

sf::FloatRect BallPad::getGlobalBounds()
{
	return m_shape.getGlobalBounds();
}

void BallPad::setCenterPos(const sf::Vector2f &pos)
{
	m_shape.setPosition(pos - sf::Vector2f(m_shape.getSize().x / 2, m_shape.getSize().y / 2));
}

void BallPad::setCenterPos(float x, float y)
{
	setCenterPos({ x, y });
}

void BallPad::offsetX(float offsetX)
{
	m_shape.move(offsetX, 0);
}

void BallPad::draw(sf::RenderTarget &target)
{
	target.draw(m_shape);
}
