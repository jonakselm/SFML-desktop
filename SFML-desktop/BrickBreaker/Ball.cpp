#include "stdafx.h"
#include "Ball.hpp"

Ball::Ball()
	:
	m_shape(10.f),
	m_velocity(500, 500)
{
	m_shape.setFillColor(sf::Color::Yellow);
	m_shape.setPosition(540, 450);
}

Ball::~Ball()
{
}

void Ball::update(float elapsedTime)
{
	sf::Vector2f toMove = { m_velocity.x * elapsedTime, m_velocity.y * elapsedTime };
	m_shape.move(toMove);
}

sf::Vector2f Ball::getVelocity() const
{
	return m_velocity;
}

sf::Vector2f Ball::getPosition() const
{
	return m_shape.getPosition();
}

sf::Vector2f Ball::getCenter() const
{
	return m_shape.getPosition() + sf::Vector2f(m_shape.getRadius(), m_shape.getRadius());
}

sf::FloatRect Ball::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

float Ball::getRadius() const
{
	return m_shape.getRadius();
}

bool Ball::intersectCenterX(const sf::FloatRect &other) const
{
	return getCenter().x > other.left && getCenter().x < other.left + other.width;
}

bool Ball::intersectCenterY(const sf::FloatRect &other) const
{
	return getCenter().y > other.top && getCenter().y < other.top + other.height;
}

void Ball::move(const sf::Vector2f &offset)
{
	m_shape.move(offset);
}

void Ball::move(float x, float y)
{
	move({ x, y });
}

void Ball::reboundX()
{
	m_velocity.x = -m_velocity.x;
}

void Ball::reboundY()
{
	m_velocity.y = -m_velocity.y;
}

void Ball::draw(sf::RenderTarget &target)
{
	target.draw(m_shape);
}
