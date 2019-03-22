#pragma once
#include "StateHandler.hpp"

class App
{
public:
	App();
	~App();

	void run(HWND hWnd);
	void init(HWND hWnd);
	bool frame();

private:

	sf::RenderWindow m_window;
	sf::Color m_windowColor;

	StateHandler m_stateHandler;
};

