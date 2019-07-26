#pragma once

#include "Shape.hpp"

class Player : public Shape
{
public:
	Player(float x, float y, sf::Color color);
	virtual ~Player();

	void update(float dt);
	void move(float x, float y);
	void jump(float jumpHeight, float startY);
	void setPosition(float x, float y);
	void setCalculatedY(float y);
	void incrementStartY(float increment);

	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
	float getCalculatedY() const;
	sf::Vector2f getSize() const;

	bool isJumping() const;

	void draw(sf::RenderTarget &target) const;

private:
	bool inFocus(sf::RenderTarget &target) const;

private:
	sf::RectangleShape m_player;
	sf::Texture m_leftTexture, m_rightTexture;
	bool m_jumping = false;
	float m_startY, m_jumpHeight;
};

