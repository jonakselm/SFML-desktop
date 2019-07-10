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
	text.setCharacterSize(20);

	pauseText.setFont(font);
	pauseText.setCharacterSize(40);
	pauseText.setPosition(420, 380);
	pauseText.setString("Pause");
}

void Practise::updateModel(sf::Window & window, StateHandler & stateHandler)
{
	if (!pause)
	{
		circle.move(speed);
	}
}

void Practise::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::Circle))
		stateHandler.Pop();

	if (showable && sf::Joystick::isButtonPressed(0, sf::Joystick::Triangle))
		showNumbers = true;
	else if (showNumbers)
		showable = false;
	if (!showable && sf::Joystick::isButtonPressed(0, sf::Joystick::Triangle))
		showNumbers = false;
	else if (!showNumbers)
		showable = true;

	if (pausable && sf::Joystick::isButtonPressed(0, sf::Joystick::Start))
		pause = true;
	else if (pause)
		pausable = false;
	if (!pausable && sf::Joystick::isButtonPressed(0, sf::Joystick::Start))
		pause = false;
	else if (!pause)
		pausable = true;

	keyHandler.handleKeyInput();

	X = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	Y =	sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	Z = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
	R = sf::Joystick::getAxisPosition(0, sf::Joystick::R);

	speed = sf::Vector2f(float(X * 0.01), float(Y * 0.01));

	if (sf::Joystick::isButtonPressed(0, sf::Joystick::Square))
	{
		speed.x *= 2;
		speed.y *= 2;
	}

	if (showNumbers)
	{
		std::stringstream ss;
		ss << "X: " << X << "		Y: " << Y << "		Z: " << Z << "		R: " << R;
		text.setString(ss.str());
	}
	else
	{
		text.setString("\0");
	}
}

void Practise::draw(sf::RenderTarget & target) const
{
	target.draw(circle);
	target.draw(text);
	if (pause)
		target.draw(pauseText);
}
