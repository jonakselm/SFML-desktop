#include "stdafx.h"
#include "MouseHandler.hpp"

void MouseButtonInfo::invoke(MouseButtonEvent e)
{
	m_func(e);
}

bool MouseButtonInfo::isPressed() const
{
	for (auto &button : m_buttons)
	{
		if (!sf::Mouse::isButtonPressed(button))
			return false;
	}
	return true;
}

std::vector<sf::Mouse::Button> MouseButtonInfo::buttons() const
{
	return m_buttons;
}

bool MouseButtonInfo::invokeIfReady()
{
	if (!isPressed())
	{
		m_wasPressed = false;
		return false;
	}

	bool isReady = !(m_isModal && m_wasPressed);
	m_wasPressed = true;

	if (isReady)
	{
		MouseButtonEvent e{ sf::Mouse::getPosition() };
		m_func(e);
	}

	return isReady;
}

MouseButtonInfo &MouseButtonHandler::addButton(MouseButtonInfo buttonInfo)
{
	return m_buttons.emplace_back(buttonInfo);
}

MouseButtonInfo &MouseButtonHandler::onButtonPressed(sf::Mouse::Button button, const MouseButtonEventFunc &func)
{
	return m_buttons.emplace_back(button, true, func);
}

MouseButtonInfo &MouseButtonHandler::whileButtonPressed(sf::Mouse::Button button, const MouseButtonEventFunc &func)
{
	return m_buttons.emplace_back(button, false, func);
}

MouseButtonInfo &MouseButtonHandler::onButtonComboPressed(std::initializer_list<sf::Mouse::Button> buttons, const MouseButtonEventFunc &func)
{
	return m_buttons.emplace_back(buttons, true, func);
}

MouseButtonInfo &MouseButtonHandler::whileButtonComboPressed(std::initializer_list<sf::Mouse::Button> buttons, const MouseButtonEventFunc &func)
{
	return m_buttons.emplace_back(buttons, false, func);
}

void MouseButtonHandler::handleButtonInput()
{
	for (auto &button : m_buttons)
	{
		button.invokeIfReady();
	}
}
