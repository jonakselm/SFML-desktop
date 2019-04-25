#include "stdafx.h"
#include "Practise.hpp"
#include "StateHandler.hpp"
#include <sstream>

Practise::Practise()
	:
	circle(30.f)
{
	circle.setFillColor(sf::Color::Green);
}


Practise::~Practise()
{
}

void Practise::init(sf::Window & window, StateHandler & stateHandler)
{
	auto kEsc = keyHandler.addKey(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});
	font.loadFromFile("data/fonts/Georgia.ttf");
	text.setFont(font);
}

void Practise::updateModel(sf::Window & window, StateHandler & stateHandler)
{
}

void Practise::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::Circle))
		stateHandler.Pop();
	keyHandler.handleKeyInput();
}

void Practise::draw(sf::RenderTarget & target)
{
	target.draw(circle);
	target.draw(text);
}
