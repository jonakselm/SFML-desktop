#pragma once
#include "State.hpp"
#include "ButtonHandler.hpp"
#include "KeyHandler.hpp"

class ControllerShow : public State
{
public:
	ControllerShow();
	virtual ~ControllerShow();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget &target);

private:
	ButtonHandler m_buttonHandler;
	KeyHandler m_keyHandler;
	sf::Font m_font;
	sf::Text XY_axis;
	sf::Text ZR_axis;
	int buttons[sf::Joystick::ButtonCount];
	sf::Text t_button;
	double X, Y, Z, R;
};

