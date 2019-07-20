#include "stdafx.h"
#include "Player.hpp"


Player::Player(float x, float y)
	:
	player(sf::Vector2f(50, 50))
{
	player.setPosition(x, y);
	player.setFillColor(sf::Color::Green);
}


Player::~Player()
{
}

sf::FloatRect Player::getGlobalBounds() const
{
	return player.getGlobalBounds();
}

void Player::draw(sf::RenderTarget & target) const
{
	target.draw(player);
}
