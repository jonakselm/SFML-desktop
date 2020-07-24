#pragma once

class BallPad
{
public:
	BallPad();
	~BallPad();

	static float getPadSpeed();

	sf::Vector2f getPosition();
	sf::Vector2f getCenterPos();
	sf::Vector2f getSize();
	sf::FloatRect getGlobalBounds();

	void setCenterPos(const sf::Vector2f &pos);
	void setCenterPos(float x, float y);

	void offsetX(float offsetX);

	void draw(sf::RenderTarget &target);

private:
	sf::RectangleShape m_shape;
	static constexpr float s_padSpeed = 5000;
};