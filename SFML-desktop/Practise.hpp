#pragma once
#include "State.hpp"
#include "KeyHandler.hpp"
#include "ButtonHandler.hpp"

class Practise : public State
{
public:
	Practise();
	virtual ~Practise();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget &target);
private:
	sf::Font font;
	sf::Text text;
	ButtonHandler buttonHandler;
	KeyHandler keyHandler;
	sf::CircleShape circle;
};

