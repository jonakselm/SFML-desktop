#pragma once

class Brick
{
public:
	Brick() = default;
	~Brick() = default;

	sf::RectangleShape shape;
	bool destroyed = false;
};