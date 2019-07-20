#include "stdafx.h"
#include "Platformer.hpp"
#include "StateHandler.hpp"


Platformer::Platformer()
	:
	player(80, 500)
{
}


Platformer::~Platformer()
{
}

void Platformer::init(sf::Window & window, StateHandler & stateHandler)
{
}

void Platformer::updateModel(sf::Window & window, StateHandler & stateHandler)
{
}

void Platformer::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
}

void Platformer::draw(sf::RenderTarget & target) const
{
	player.draw(target);
}
