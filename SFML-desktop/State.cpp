#include "stdafx.h"
#include "State.hpp"

bool State::pollEvent(sf::Window &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			return false;

		case sf::Event::LostFocus:
			m_respondable = false;
			return true;

		case sf::Event::GainedFocus:
			m_respondable = true;
			return true;
		}
	}

	return true;
}
