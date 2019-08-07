#include "stdafx.h"
#include "PlatformPlayer.hpp"

PlatformPlayer::PlatformPlayer(float x, float y, sf::Color color, CameraControl &cameraControl)
	:
	m_player(sf::Vector2f(x, y)),
	m_cameraControl(cameraControl)
{
	m_player.setFillColor(color);
	//m_rightTexture.loadFromFile("data/images/rightpac.png");
	//m_leftTexture.loadFromFile("data/images/leftpac.png");
	m_player.setTexture(&m_rightTexture);
}


PlatformPlayer::~PlatformPlayer()
{
}

void PlatformPlayer::update(float dt)
{
	if (m_jumping)
	{
		if (m_player.getPosition().y + m_player.getSize().y > m_startY - m_jumpHeight)
			m_player.move(0, -0.5f * dt);
		else
			m_jumping = false;
	}

	m_cameraControl.growIfNeeded();
}

void PlatformPlayer::move(float x, float y)
{
	auto old = m_player.getPosition();
	m_player.move(x, y);

	if (old.x < m_player.getPosition().x)
		m_player.setTexture(&m_rightTexture);
	else if (old.x > m_player.getPosition().x)
		m_player.setTexture(&m_leftTexture);
}

void PlatformPlayer::jump(float jumpHeight, float startY)
{
	m_startY = startY;
	m_jumpHeight = jumpHeight;
	m_jumping = true;
}

void PlatformPlayer::setPosition(float x, float y)
{
	m_player.setPosition(x, y);
}

void PlatformPlayer::setCalculatedY(float y)
{
	m_player.setPosition(m_player.getPosition().x, y - m_player.getSize().y);
}

sf::FloatRect PlatformPlayer::getGlobalBounds() const
{
	return m_player.getGlobalBounds();
}

sf::Vector2f PlatformPlayer::getPosition() const
{
	return m_player.getPosition();
}

float PlatformPlayer::getCalculatedY() const
{
	return m_player.getPosition().y + m_player.getSize().y;
}

sf::Vector2f PlatformPlayer::getSize() const
{
	return m_player.getSize();
}

bool PlatformPlayer::isJumping() const
{
	return m_jumping;
}

void PlatformPlayer::draw(sf::RenderTarget & target) const
{
	if (inFocus(target))
		target.draw(m_player);
}

bool PlatformPlayer::inFocus(sf::RenderTarget & target) const
{
	if (m_player.getPosition().x + m_player.getSize().x >= 0 &&
		m_player.getPosition().x <= target.getSize().x &&
		m_player.getPosition().y + m_player.getSize().y >= 0 &&
		m_player.getPosition().y <= target.getSize().y)
		return true;

	return false;
}
