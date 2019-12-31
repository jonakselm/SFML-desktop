#include "stdafx.h"
#include "Practise.hpp"
#include "../StateHandler.hpp"
#include <sstream>
#include "../SFML-ext.hpp"

Practise::Practise()
	:
	m_spawned{ false }
{
}


Practise::~Practise()
{
}

void Practise::init(sf::Window & window, StateHandler & stateHandler)
{
	keyHandler.onKeyPressed(sf::Keyboard::Escape, [&]
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
}

void Practise::handleExtraEvents(sf::Window & window, StateHandler & stateHandler)
{
	keyHandler.handleKeyInput();

	for (int index = 0; index < sf::Joystick::Count; index++)
	{
		if (sf::Joystick::isConnected(index))
		{
			unsigned int id = sf::Joystick::getIdentification(index).productId;

			if (!m_spawned[index] && ((sfExt::GameCube::isButtonPressed(index, sfExt::GameCube::L) &&
				sfExt::GameCube::isButtonPressed(index, sfExt::GameCube::R)) ||
				sfExt::Ps3::isButtonPressed(index, sfExt::Ps3::PS_Btn)))
			{
				auto &player = m_players[index];
				player.setRadius(30.f);
				player.setFillColor(sf::Color(std::rand() % 200 + 50, std::rand() % 200 + 50, std::rand() % 200 + 50));
				m_spawned[index] = true;
			}

			if (!m_pause && m_spawned[index])
			{
				sf::Vector2f speed;

				if (sf::Joystick::getAxisPosition(index, sf::Joystick::X) > 60)
					speed.x = 2;
				else if (sf::Joystick::getAxisPosition(index, sf::Joystick::X) < 60 &&
					sf::Joystick::getAxisPosition(index, sf::Joystick::X) > 20)
					speed.x = 1;
				else if (sf::Joystick::getAxisPosition(index, sf::Joystick::X) < -60)
					speed.x = -2;
				else if (sf::Joystick::getAxisPosition(index, sf::Joystick::X) > -60 &&
					sf::Joystick::getAxisPosition(index, sf::Joystick::X) < -20)
					speed.x = -1;
				else
					speed.x = 0;

				if (sf::Joystick::getAxisPosition(index, sf::Joystick::Y) > 60)
					speed.y = 2;
				else if (sf::Joystick::getAxisPosition(index, sf::Joystick::Y) < 60 &&
					sf::Joystick::getAxisPosition(index, sf::Joystick::Y) > 20)
					speed.y = 1;
				else if (sf::Joystick::getAxisPosition(index, sf::Joystick::Y) < -60)
					speed.y = -2;
				else if (sf::Joystick::getAxisPosition(index, sf::Joystick::Y) > -60 &&
					sf::Joystick::getAxisPosition(index, sf::Joystick::Y) < -20)
					speed.y = -1;
				else
					speed.y = 0;
				
				m_players[index].move(speed);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////
	// TODO: Make showNumbers and pause available for all players
	if (m_showable && (sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Select) ||
		sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::Z)))
		m_showNumbers = true;
	else if (m_showNumbers)
		m_showable = false;
	if (!m_showable && (sf::Joystick::isButtonPressed(0, sfExt::Ps3::Select) ||
		sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::Z)))
		m_showNumbers = false;
	else if (!m_showNumbers)
		m_showable = true;

	if (m_pausable && (sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Start) ||
		sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::Start)))
		m_pause = true;
	else if (m_pause)
		m_pausable = false;
	if (!m_pausable && (sfExt::Ps3::isButtonPressed(0, sfExt::Ps3::Start) ||
		sfExt::GameCube::isButtonPressed(0, sfExt::GameCube::Start)))
		m_pause = false;
	else if (!m_pause)
		m_pausable = true;
	///////////////////////////////////////////////////////////////////////////////////

	if (sf::Joystick::isButtonPressed(0, sfExt::Ps3::Circle) ||
		sf::Joystick::isButtonPressed(0, sfExt::GameCube::B))
		stateHandler.Pop();

	X = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	Y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	Z = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
	R = sf::Joystick::getAxisPosition(0, sf::Joystick::R);

	if (m_showNumbers)
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

void Practise::draw(sf::RenderTarget & target)
{
	for (int i = 0; i < m_players.size(); i++)
	{
		target.draw(m_players[i]);
	}

	target.draw(text);
	if (m_pause)
		target.draw(pauseText);
}
