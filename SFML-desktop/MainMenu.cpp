#include "stdafx.h"
#include "MainMenu.hpp"
#include "StateHandler.hpp"
#include "SnakeGame.hpp"

MainMenu::MainMenu()
{
	m_font.loadFromFile("data/fonts/Georgia.ttf");
	m_buttonHandler.setFont(m_font);
}


MainMenu::~MainMenu()
{
}

void MainMenu::init(sf::Window &window, StateHandler &stateHandler)
{
	m_buttonHandler.setDefaultSize(300, 60);
	m_buttonHandler.setNextPosition(150, 100);
	m_buttonHandler.setSpacing(10);

	m_buttonHandler.addButton("Snake game", [&]
		{
			stateHandler.Push<SnakeGame>();
		});
}

void MainMenu::updateModel(sf::Window & window, StateHandler &stateHandler)
{
	m_buttonHandler.handleInput(window);
}

void MainMenu::draw(sf::RenderTarget & target)
{
	m_buttonHandler.draw(target);
}
