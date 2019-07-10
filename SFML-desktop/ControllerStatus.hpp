#pragma once
#include "State.hpp"
#include "ButtonHandler.hpp"
#include "KeyHandler.hpp"
#include <array>

class ControllerStatus : public State
{
public:
	ControllerStatus();
	virtual ~ControllerStatus();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget &target) const;

private:
	ButtonHandler m_buttonHandler;
	KeyHandler m_keyHandler;
	sf::Font m_font;
	sf::Text XY_axis;
	sf::Text ZR_axis;
	std::array<std::string, sf::Joystick::ButtonCount> arr_buttonText;
	sf::Text m_buttonText;
	double X, Y, Z, R;
};

