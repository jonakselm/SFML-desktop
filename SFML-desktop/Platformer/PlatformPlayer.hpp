#pragma once

#include "../Shape.hpp"
#include "CameraControl.hpp"

class PlatformPlayer : public Shape
{
public:
	PlatformPlayer(float x, float y, sf::Color color, CameraControl &cameraControl);
	virtual ~PlatformPlayer();

	void update(float dt);
	void move(float x, float y);
	void jump(float jumpHeight, float startY);
	void setPosition(float x, float y);
	void setCalculatedY(float y);

	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
	float getCalculatedY() const;
	sf::Vector2f getSize() const;

	bool isJumping() const;

	void draw(sf::RenderTarget &target) const;

private:
	bool inFocus(sf::RenderTarget &target) const;

private:
	CameraControl &m_cameraControl;
	sf::RectangleShape m_player;
	sf::Texture m_leftTexture, m_rightTexture;
	bool m_jumping = false;
	float m_startY, m_jumpHeight;
};

