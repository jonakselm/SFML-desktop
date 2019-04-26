#include "stdafx.h"
#include "ControllerShow.hpp"
#include "StateHandler.hpp"
#include <sstream>


ControllerShow::ControllerShow()
{
}


ControllerShow::~ControllerShow()
{
}

void ControllerShow::init(sf::Window & window, StateHandler & stateHandler)
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

	t_button.setFont(m_font);
	t_button.setCharacterSize(20);
	t_button.setPosition(300, 300); 
}

void ControllerShow::updateModel(sf::Window & window, StateHandler & stateHandler)
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
		std::string temp;
		if (i == sf::Joystick::Select)
			temp = "Select";
		else if (i == sf::Joystick::L3)
			temp = "L3";
		else if (i == sf::Joystick::R3)
			temp = "R3";
		else if (i == sf::Joystick::Start)
			temp = "Start";
		else if (i == sf::Joystick::Up)
			temp = "Up";
		else if (i == sf::Joystick::Right)
			temp = "Right";
		else if (i == sf::Joystick::Down)
			temp = "Down";
		else if (i == sf::Joystick::Left)
			temp = "Left";
		else if (i == sf::Joystick::L2)
			temp = "L2";
		else if (i == sf::Joystick::R2)
			temp = "R2";
		else if (i == sf::Joystick::L1)
			temp = "L1";
		else if (i == sf::Joystick::R1)
			temp = "R1";
		else if (i == sf::Joystick::Triangle)
			temp = "Triangle";
		else if (i == sf::Joystick::Circle)
			temp = "Circle";
		else if (i == sf::Joystick::Cross)
			temp = "Cross";
		else if (i == sf::Joystick::Square)
			temp = "Square";
		else if (i == sf::Joystick::PS_Btn)
			temp = "Ps Button";

		if (sf::Joystick::isButtonPressed(0, i))
			ss_button << temp;
	}
	t_button.setString(ss_button.str());
}

void ControllerShow::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	m_buttonHandler.handleInput(window);
	m_keyHandler.handleKeyInput();

	X = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	Y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	Z = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
	R = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
}

void ControllerShow::draw(sf::RenderTarget & target)
{
	target.draw(XY_axis);
	target.draw(ZR_axis);
	target.draw(t_button);
}
