#pragma once
#include "State.hpp"
#include "ButtonHandler.hpp"
#include "KeyHandler.hpp"
#include "SnakeGame.hpp"
#include <sstream>
#include <array>

class SnakeInit : public State
{
public:
	SnakeInit();
	virtual ~SnakeInit();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget& target) const;

private:
	ButtonHandler buttonHandler;
	KeyHandler keyHandler;

	sf::Font font;
	sf::Text nColorsText, startColorText, colorInitText, incrementText,
		nColorInstr, startColorInstr, colorInitInstr, incrementInstr;

	std::array<sf::Color, 3> colorArray;
	std::array<std::string, 3> stringArray;
	std::array<ColorInit, 3> initArray;
	int chosenStart, chosenInit;

	int nColors;
	sf::Color startColor;
	ColorInit colorInit;
	int increment;
};

