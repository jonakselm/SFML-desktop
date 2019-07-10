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
	void draw(sf::RenderTarget &target) const;

private:
	float X, Y, Z, R;
	sf::Vector2f speed;
	sf::Font font;
	sf::Text text;
	sf::Text pauseText;
	ButtonHandler buttonHandler;
	KeyHandler keyHandler;
	sf::CircleShape circle;
	bool showNumbers = false;
	bool showable = true;
	bool pause = false;
	bool pausable = true;
};

