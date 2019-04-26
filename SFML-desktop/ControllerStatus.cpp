#include "stdafx.h"
#include "ControllerStatus.hpp"
#include "StateHandler.hpp"
#include <sstream>


ControllerStatus::ControllerStatus()
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

	t_button.setFont(m_font);
	t_button.setCharacterSize(20);
	t_button.setPosition(300, 300);

	for (int i = 0; i < arr_buttons.size(); i++)
	{
		if (i == sf::Joystick::Select)
			arr_buttons[i] = "Select";
		else if (i == sf::Joystick::L3)
			arr_buttons[i] = "L3";
		else if (i == sf::Joystick::R3)
			arr_buttons[i] = "R3";
		else if (i == sf::Joystick::Start)
			arr_buttons[i] = "Start";
		else if (i == sf::Joystick::Up)
			arr_buttons[i] = "Up";
		else if (i == sf::Joystick::Right)
			arr_buttons[i] = "Right";
		else if (i == sf::Joystick::Down)
			arr_buttons[i] = "Down";
		else if (i == sf::Joystick::Left)
			arr_buttons[i] = "Left";
		else if (i == sf::Joystick::L2)
			arr_buttons[i] = "L2";
		else if (i == sf::Joystick::R2)
			arr_buttons[i] = "R2";
		else if (i == sf::Joystick::L1)
			arr_buttons[i] = "L1";
		else if (i == sf::Joystick::R1)
			arr_buttons[i] = "R1";
		else if (i == sf::Joystick::Triangle)
			arr_buttons[i] = "Triangle";
		else if (i == sf::Joystick::Circle)
			arr_buttons[i] = "Circle";
		else if (i == sf::Joystick::Cross)
			arr_buttons[i] = "Cross";
		else if (i == sf::Joystick::Square)
			arr_buttons[i] = "Square";
		else if (i == sf::Joystick::PS_Btn)
			arr_buttons[i] = "PS Button";
	}
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
			ss_button << arr_buttons[i];
	}
	t_button.setString(ss_button.str());
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

void ControllerStatus::draw(sf::RenderTarget & target)
{
	target.draw(XY_axis);
	target.draw(ZR_axis);
	target.draw(t_button);
}
