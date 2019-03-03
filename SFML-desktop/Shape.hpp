#pragma once

class Shape
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	virtual void draw(sf::RenderTarget &target) const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;
	bool intersects(Shape & other) const
	{
		return other.getGlobalBounds().intersects(getGlobalBounds());
	}
};
