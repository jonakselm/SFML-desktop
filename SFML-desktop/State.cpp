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
			window.close();
			return false;
			break;
		}
	}

	return true;
}
