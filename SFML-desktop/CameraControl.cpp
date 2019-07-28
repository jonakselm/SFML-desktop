#include "stdafx.h"
#include "CameraControl.hpp"


void CameraControl::init(sf::RenderTexture & texture, sf::Sprite & renderSprite, sf::Vector2i windowSize)
{
	m_pTexture = &texture;
	m_pSprite = &renderSprite;
	m_windowSize = windowSize;
}

void CameraControl::updateWindowSize(sf::Vector2i windowSize)
{
	m_windowSize = windowSize;
}

void CameraControl::setCentrePos(sf::IntRect centralizedObject)
{
	auto newX = m_windowSize.x / 2 - centralizedObject.width / 2 - centralizedObject.left;
	auto newY = m_windowSize.y / 2 - centralizedObject.height / 2 - centralizedObject.top;

	m_pSprite->setPosition(static_cast<float>(newX), static_cast<float>(newY));
}

void CameraControl::growIfNeeded()
{
	auto size = m_pTexture->getSize();
	auto pos = -m_pSprite->getPosition();

	if (pos.x + 1000 > size.x)
	{
		m_pTexture->create(size.x + 5000, size.y);
		m_pSprite->setTexture(m_pTexture->getTexture());
		m_pSprite->setTextureRect(sf::IntRect(0, 0, size.x + 5000, size.y));
	}
}