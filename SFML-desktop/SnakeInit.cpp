#include "stdafx.h"
#include "SnakeInit.hpp"
#include "StateHandler.hpp"

SnakeInit::SnakeInit()
	:
	nColors(1),
	startColor(sf::Color::Red),
	colorInit(ColorInit::Red),
	increment(0),
	chosenStart(0),
	chosenInit(0)
{
}


SnakeInit::~SnakeInit()
{
}

void SnakeInit::init(sf::Window & window, StateHandler & stateHandler)
{
	keyHandler.addKey(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});

	for (int i = 0; i < stringArray.size(); i++)
	{
		switch (i)
		{
		case 0:
			stringArray[i] = "Red";
			break;
		case 1:
			stringArray[i] = "Green";
			break;
		case 2:
			stringArray[i] = "Blue";
			break;
		}
	}

	for (int i = 0; i < colorArray.size(); i++)
	{
		switch (i)
		{
		case 0:
			colorArray[i] = sf::Color::Red;
			break;
		case 1:
			colorArray[i] = sf::Color::Green;
			break;
		case 2:
			colorArray[i] = sf::Color::Blue;
			break;
		}
	}

	for (int i = 0; i < initArray.size(); i++)
	{
		switch (i)
		{
		case 0:
			initArray[i] = ColorInit::Red;
			break;
		case 1:
			initArray[i] = ColorInit::Green;
			break;
		case 2:
			initArray[i] = ColorInit::Blue;
			break;
		}
	}

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


	buttonHandler.setFont(font);
	buttonHandler.setDefaultSize(40, 40);
	buttonHandler.setTextSize(40);
	buttonHandler.setNextPosition(250, 210);
	buttonHandler.setSpacing(70);

	auto bNColors0 = buttonHandler.addButton("<", [&]
		{
			if (nColors > 1)
				nColors -= 1;
			else
				nColors = 30;
		});
	auto bStartColor0 = buttonHandler.addButton("<", [&]
		{
			if (chosenStart > 0)
				chosenStart -= 1;
			else
				chosenStart = 2;

			startColor = colorArray[chosenStart];
		});
	auto bColorInit0 = buttonHandler.addButton("<", [&]
		{
			if (chosenInit > 0)
				chosenInit -= 1;
			else
				chosenInit = 2;

			colorInit = initArray[chosenInit];
		});
	auto bIncrement0 = buttonHandler.addButton("<", [&]
		{
			if (increment > 1)
				increment -= 1;
			else
				increment = 250;
		});

	buttonHandler.setNextPosition(700, 210);

	auto bNColors1 = buttonHandler.addButton(">", [&]
		{
			if (nColors < 30)
				nColors += 1;
			else
				nColors = 1;
		});
	auto bStartColor1 = buttonHandler.addButton(">", [&]
		{
			if (chosenStart < 2)
				chosenStart += 1;
			else
				chosenStart = 0;

			startColor = colorArray[chosenStart];
		});
	auto bColorInit1 = buttonHandler.addButton(">", [&]
		{
			if (chosenInit < 2)
				chosenInit += 1;
			else
				chosenInit = 0;

			colorInit = initArray[chosenInit];
		});
	auto bIncrement1 = buttonHandler.addButton(">", [&]
		{
			if (increment < 250)
				increment += 1;
			else
				increment = 1;
		});

	buttonHandler.setNextPosition(400, 650);
	buttonHandler.setDefaultSize(200, 50);
	buttonHandler.setTextSize(30);

	auto bStart = buttonHandler.addButton("Start Game", [&]
		{
				stateHandler.Push<SnakeGame>(nColors, startColor, colorInit, increment);
		});
}

void SnakeInit::updateModel(sf::Window & window, StateHandler & stateHandler)
{
	nColorsText.setString(std::to_string(nColors));
	startColorText.setString(stringArray[chosenStart]);
	colorInitText.setString(stringArray[chosenInit]);
	incrementText.setString(std::to_string(increment));
}

void SnakeInit::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	buttonHandler.handleInput(window);
	keyHandler.handleKeyInput();
}

void SnakeInit::draw(sf::RenderTarget & target) const
{
	buttonHandler.draw(target);

	target.draw(nColorsText);
	target.draw(startColorText);
	target.draw(colorInitText);
	target.draw(incrementText);

	target.draw(nColorInstr);
	target.draw(startColorInstr);
	target.draw(colorInitInstr);
	target.draw(incrementInstr);
}
