#include "stdafx.h"
#include "ControllerStatus.hpp"
#include "StateHandler.hpp"
#include <sstream>
#include "SFML-ext.hpp"


ControllerStatus::ControllerStatus()
	:
	arr_buttonText{ "Select ", "L3 ", "R3 ", "Start ", "Up ", "Right ", "Down ", "Left ",
		"L2 ", "R2 ", "L1 ", "R1 ", "Triangle ", "Circle ", "Cross ", "Square ", "PS Button " }
{
}


ControllerStatus::~ControllerStatus()
{
}

void ControllerStatus::init(sf::Window & window, StateHandler & stateHandler)
{
	auto kEsc = m_keyHandler.addKey(sf::Keyboard::Escape, [&]
		{
			stateHandler.Pop();
		});

	m_font.loadFromFile("data/fonts/Georgia.ttf");

	XY_axis.setFont(m_font);
	XY_axis.setCharacterSize(20);
	XY_axis.setPosition(0, 0);

	ZR_axis.setFont(m_font);
	ZR_axis.setCharacterSize(20);
	ZR_axis.setPosition(600, 0);

	m_buttonText.setFont(m_font);
	m_buttonText.setCharacterSize(20);
	m_buttonText.setPosition(300, 300);
}

void ControllerStatus::updateModel(sf::Window & window, StateHandler & stateHandler)
{
	std::stringstream ss_XY;
	ss_XY << "X: " << X << "		Y: " << Y;
	XY_axis.setString(ss_XY.str());

	std::stringstream ss_ZR;
	ss_ZR << "Z: " << Z << "		R: " << R;
	ZR_axis.setString(ss_ZR.str());

	std::stringstream ss_button;
	ss_button << "Button pressed:	";
	for (int i = 0; i < sf::Joystick::ButtonCount; i++)
	{
		if (sf::Joystick::isButtonPressed(0, i))
			ss_button << arr_buttonText[i];
	}
	m_buttonText.setString(ss_button.str());
}

void ControllerStatus::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	m_buttonHandler.handleInput(window);
	m_keyHandler.handleKeyInput();

	X = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	Y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	Z = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
	R = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
}

void ControllerStatus::draw(sf::RenderTarget & target) const
{
	target.draw(XY_axis);
	target.draw(ZR_axis);
	target.draw(m_buttonText);
}
