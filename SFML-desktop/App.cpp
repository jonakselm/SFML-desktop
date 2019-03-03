#include "stdafx.h"
#include "App.hpp"
#include "MainMenu.hpp"

App::App()
{
}


App::~App()
{
}

void App::init(HWND hWnd)
{
	m_window.create(hWnd);
	m_stateHandler.Push<MainMenu>();
}

void App::run(HWND hWnd)
{
	init(hWnd);
	while (frame());
}

bool App::frame()
{
	if (m_stateHandler.InTransition())
		m_stateHandler.PerformTransition(m_window, m_stateHandler);

	auto state = m_stateHandler.GetState();
	if (!state)
		return false;

	if (!state->pollEvent(m_window))
		return false;

	state->updateModel(m_window, m_stateHandler);

	// Draw
	m_window.clear(m_windowColor);
	state->draw(m_window);
	m_window.display();

	return true;
}
