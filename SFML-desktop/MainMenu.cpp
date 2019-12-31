#include "stdafx.h"
#include "MainMenu.hpp"
#include "StateHandler.hpp"
#include "Snake/SnakeGame.hpp"
#include "Practise/Practise.hpp"
#include "ControllerStatus/ControllerStatus.hpp"
#include "Snake/SnakeInit.hpp"
#include "Platformer/Platformer.hpp"
#include "Minesweeper/Minesweeper.hpp"

MainMenu::MainMenu()
{
	m_font.loadFromFile("data/fonts/Georgia.ttf");
	m_buttonHandler.setFont(m_font);

	std::srand(static_cast<unsigned>(std::time(0)));
}


MainMenu::~MainMenu()
{
}

void MainMenu::init(sf::Window &window, StateHandler &stateHandler)
{
	m_buttonHandler.setDefaultSize(400, 60);
	m_buttonHandler.setNextPosition(150, 100);
	m_buttonHandler.setSpacing(10);

	m_buttonHandler.addButton("Snake Game", [&]
		{
			stateHandler.Push<SnakeGame>(30, sf::Color(255, 0, 0), Snake::ColorInit::Red, 15);
		});
	m_buttonHandler.addButton("Customizable Snake", [&]
		{
			stateHandler.Push<SnakeInit>();
		});
	m_buttonHandler.addButton("Practise", [&]
		{
			stateHandler.Push<Practise>();
		});
	m_buttonHandler.addButton("Show Controller Inputs", [&]
		{
			stateHandler.Push<ControllerStatus>();
		});
	m_buttonHandler.addButton("Platformer", [&]
		{
			stateHandler.Push<Platformer>();
		});
	m_buttonHandler.addButton("Minesweeper", [&]
		{
			stateHandler.Push<Minesweeper>();
		});
}

void MainMenu::updateModel(sf::Window &window, StateHandler &stateHandler)
{
}

void MainMenu::handleExtraEvents(sf::Window &window, StateHandler &stateHandler)
{
	m_buttonHandler.handleInput(window);
}

void MainMenu::draw(sf::RenderTarget & target)
{
	m_buttonHandler.draw(target);
}
