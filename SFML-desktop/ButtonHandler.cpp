#include "stdafx.h"
#include "ButtonHandler.hpp"
#include "SFML-ext.hpp"

void ButtonHandler::setTextSize(unsigned int size)
{
	m_textSize = size;
}

unsigned int ButtonHandler::getTextSize() const
{
	return m_textSize;
}

void ButtonHandler::setSpacing(int spacing)
{
	m_spacing = spacing;
}

int ButtonHandler::getSpacing() const
{
	return m_spacing;
}

void ButtonHandler::setNextPosition(int x, int y)
{
	m_xCurr = x;
	m_yCurr = y;
}

std::pair<int, int> ButtonHandler::getNextPosition() const
{
	return std::make_pair(m_xCurr, m_yCurr);
}

void ButtonHandler::setDefaultSize(int width, int height)
{
	m_defaultWidth = width;
	m_defaultHeight = height;
}

std::pair<int, int> ButtonHandler::getDefaultSize() const
{
	return std::make_pair(m_defaultWidth, m_defaultHeight);
}

Button &ButtonHandler::addButton(const std::string &text, const std::function<void()> &func)
{
	auto &button = m_buttons.emplace_back(*m_pFont);
	if (m_buttons.size() == 1)
	{
		button.select();
		m_it = m_buttons.begin();
	}

	button.setTextSize(m_textSize);
	button.setText(text);
	button.setSize(m_defaultWidth, m_defaultHeight);
	button.setPosition(m_xCurr, m_yCurr);
	button.setActionHandler(func);

	auto bounds = button.getGlobalBounds();
	m_yCurr = int(bounds.top + bounds.height + m_spacing);

	return button;
}

bool ButtonHandler::toogleInputMode()
{
	if (!m_mouseControl)
	{
		m_lastMousePos = sf::Mouse::getPosition();
		m_mouseControl = false;
	}

	auto currMousePos = sf::Mouse::getPosition();
	if (m_lastMousePos != currMousePos)
	{
		m_lastMousePos = currMousePos;
		m_mouseControl = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
		|| sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Up)
		|| sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Down)
		|| sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Cross)
		|| sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::Up)
		|| sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::Down)
		|| sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::A))
	{
		m_mouseControl = false;
	}

	return *m_mouseControl;
}

void ButtonHandler::handleInput(sf::Window &window)
{
	toogleInputMode() ? handleMouseEvents(window) : handleKeyEvents(window);
}

void ButtonHandler::draw(sf::RenderTarget &target) const
{
	for (auto &button : m_buttons)
		button.draw(target);
}

void ButtonHandler::handleKeyEvents(sf::Window &window)
{
	m_time = m_clock.getElapsedTime();

	if (m_time >= m_updatePeriod)
		m_updatable = true;

	if (m_buttons.empty())
		return;

	if (m_it._Ptr == nullptr)
	{
		m_it = m_buttons.begin();
		m_it->select();
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		|| sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Up)
		|| sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::Up))
		&& m_updatable)
	{
		m_updatable = false;
		m_clock.restart();

		m_it->deselect();
		if (m_it == m_buttons.begin())
			m_it = --m_buttons.end();
		else
			m_it--;
		m_it->select();
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		|| sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Down)
		|| sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::Down))
		&& m_updatable)
	{
		m_updatable = false;
		m_clock.restart();

		m_it->deselect();
		if (m_it == --m_buttons.end())
			m_it = m_buttons.begin();
		else
			m_it++;
		m_it->select();
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
		|| sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Cross)
		|| sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::A))
		&& m_updatable)
	{
		m_updatable = false;
		m_clock.restart();

		m_it->invoke();
	}
}

void ButtonHandler::handleMouseEvents(sf::Window &window)
{
	m_time = m_clock.getElapsedTime();

	if (m_time >= m_updatePeriod)
		m_updatable = true;

	m_it._Ptr = nullptr;
	auto pos = sf::Mouse::getPosition(window);
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
	{
		if (it->contains(pos.x, pos.y))
		{
			m_it = it;
			it->select();
		}
		else
		{
			it->deselect();
		}
	}

	if (m_it._Ptr && sf::Mouse::isButtonPressed(sf::Mouse::Left)
		&& m_updatable)
	{
		m_updatable = false;
		m_clock.restart();

		m_it->invoke();
	}
}
