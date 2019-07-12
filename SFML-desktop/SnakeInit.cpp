#include "stdafx.h"
#include "SnakeInit.hpp"
#include "StateHandler.hpp"

SnakeInit::SnakeInit()
	:
	m_nColors(1),
	m_startColor(sf::Color::Red),
	m_colorInit(Snake::ColorInit::Red),
	m_increment(0),
	chosenStart(0),
	chosenInit(0),
	m_colorArray{ sf::Color::Red, sf::Color::Green, sf::Color::Blue },
	m_stringArray{ "Red", "Green", "Blue", "All" },
	m_initArray{ Snake::ColorInit::Red, Snake::ColorInit::Green, Snake::ColorInit::Blue, Snake::ColorInit::All }
{
}


SnakeInit::~SnakeInit()
{
}

void SnakeInit::init(sf::Window & window, StateHandler & stateHandler)
{
	m_keyHandler.addKey(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});

	font.loadFromFile("data/fonts/Georgia.ttf");

	nColorsText.setFont(font);
	startColorText.setFont(font);
	colorInitText.setFont(font);
	incrementText.setFont(font);

	nColorsText.setPosition(480, 210);
	startColorText.setPosition(470, 320);
	colorInitText.setPosition(470, 430);
	incrementText.setPosition(480, 540);


	nColorInstr.setFont(font);
	startColorInstr.setFont(font);
	colorInitInstr.setFont(font);
	incrementInstr.setFont(font);

	nColorInstr.setPosition(250, 170);
	startColorInstr.setPosition(250, 280);
	colorInitInstr.setPosition(250, 390);
	incrementInstr.setPosition(250, 500);

	nColorInstr.setString("Number of Colors");
	startColorInstr.setString("Start Color");
	colorInitInstr.setString("What color it will transition through");
	incrementInstr.setString("How much the colors will increment or decrement");


	m_buttonHandler.setFont(font);
	m_buttonHandler.setDefaultSize(40, 40);
	m_buttonHandler.setTextSize(40);
	m_buttonHandler.setNextPosition(250, 210);
	m_buttonHandler.setSpacing(70);

	auto bNColors0 = m_buttonHandler.addButton("<", [this]
		{
			if (m_nColors > 1)
				m_nColors -= 1;
			else
				m_nColors = 30;
		});
	auto bStartColor0 = m_buttonHandler.addButton("<", [this]
		{
			if (chosenStart > 0)
				chosenStart -= 1;
			else
				chosenStart = (int)m_colorArray.size() - 1;

			m_startColor = m_colorArray[chosenStart];
		});
	auto bColorInit0 = m_buttonHandler.addButton("<", [this]
		{
			if (chosenInit > 0)
				chosenInit -= 1;
			else
				chosenInit = (int)m_initArray.size() - 1;

			m_colorInit = m_initArray[chosenInit];
		});
	auto bIncrement0 = m_buttonHandler.addButton("<", [this]
		{
			if (m_increment > 1)
				m_increment -= 1;
			else
				m_increment = 250;
		});

	m_buttonHandler.setNextPosition(700, 210);

	auto bNColors1 = m_buttonHandler.addButton(">", [this]
		{
			if (m_nColors < 30)
				m_nColors += 1;
			else
				m_nColors = 1;
		});
	auto bStartColor1 = m_buttonHandler.addButton(">", [this]
		{
			if (chosenStart < (int)m_colorArray.size() - 1)
				chosenStart += 1;
			else
				chosenStart = 0;

			m_startColor = m_colorArray[chosenStart];
		});
	auto bColorInit1 = m_buttonHandler.addButton(">", [this]
		{
			if (chosenInit < (int)m_initArray.size() - 1)
				chosenInit += 1;
			else
				chosenInit = 0;

			m_colorInit = m_initArray[chosenInit];
		});
	auto bIncrement1 = m_buttonHandler.addButton(">", [this]
		{
			if (m_increment < 250)
				m_increment += 1;
			else
				m_increment = 1;
		});

	m_buttonHandler.setNextPosition(400, 650);
	m_buttonHandler.setDefaultSize(200, 50);
	m_buttonHandler.setTextSize(30);

	auto bStart = m_buttonHandler.addButton("Start Game", [&]
		{
				stateHandler.Push<SnakeGame>(m_nColors, m_startColor, m_colorInit, m_increment);
		});
}

void SnakeInit::updateModel(sf::Window & window, StateHandler & stateHandler)
{
	nColorsText.setString(std::to_string(m_nColors));
	startColorText.setString(m_stringArray[chosenStart]);
	colorInitText.setString(m_stringArray[chosenInit]);
	incrementText.setString(std::to_string(m_increment));
}

void SnakeInit::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	m_buttonHandler.handleInput(window);
	m_keyHandler.handleKeyInput();
}

void SnakeInit::draw(sf::RenderTarget & target) const
{
	m_buttonHandler.draw(target);

	target.draw(nColorsText);
	target.draw(startColorText);
	target.draw(colorInitText);
	target.draw(incrementText);

	target.draw(nColorInstr);
	target.draw(startColorInstr);
	target.draw(colorInitInstr);
	target.draw(incrementInstr);
}
