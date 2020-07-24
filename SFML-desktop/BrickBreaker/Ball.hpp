#pragma once

class Ball
{
public:
	Ball();
	~Ball();

	void update(float elapsedTime);

	sf::Vector2f getVelocity() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getCenter() const;
	sf::FloatRect getGlobalBounds() const;
	float getRadius() const;
	
	bool intersectCenterX(const sf::FloatRect &other) const;
	bool intersectCenterY(const sf::FloatRect &other) const;

	void move(const sf::Vector2f &offset);
	void move(float x, float y);

	void reboundX();
	void reboundY();

	void draw(sf::RenderTarget &target);

private:
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
};