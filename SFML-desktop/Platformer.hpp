#pragma once

#include "State.hpp"
#include "Player.hpp"

class Platformer : public State
{
public:
	Platformer();
	virtual ~Platformer();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget &target) const;

private:
	Player player;
};

