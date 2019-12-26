#pragma once
#include "../State.hpp"
#include "../ButtonHandler.hpp"
#include "../KeyHandler.hpp"
#include "SnakeGame.hpp"

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
	ButtonHandler m_buttonHandler;
	KeyHandler m_keyHandler;

	sf::Font font;
	sf::Text nColorsText, startColorText, colorInitText, incrementText,
		nColorInstr, startColorInstr, colorInitInstr, incrementInstr;

	std::array<sf::Color, 3> m_colorArray;
	std::array<std::string, 4> m_stringArray;
	std::array<Snake::ColorInit, 4> m_initArray;
	int chosenStart, chosenInit;

	int m_nColors;
	sf::Color m_startColor;
	Snake::ColorInit m_colorInit;
	int m_increment;
};

