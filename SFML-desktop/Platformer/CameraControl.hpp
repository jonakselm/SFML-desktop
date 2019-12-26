#pragma once

class CameraControl
{
public:
	CameraControl() = default;
	CameraControl(sf::RenderTexture &texture, sf::Sprite &renderSprite, sf::Vector2i windowSize = {0, 0}) :
		m_pTexture(&texture), m_pSprite(&renderSprite), m_windowSize(windowSize) {}
	
	void init(sf::RenderTexture &texture, sf::Sprite &renderSprite, sf::Vector2i windowSize = { 0, 0 });
	void updateWindowSize(sf::Vector2i windowSize);
	void setCentrePos(sf::IntRect centralizedObject);
	
	void growIfNeeded();

private:

	sf::Sprite *m_pSprite = nullptr;
	sf::RenderTexture *m_pTexture = nullptr;
	sf::Vector2i m_windowSize = { 0, 0 };
};

