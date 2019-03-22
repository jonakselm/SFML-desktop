#pragma once
#include "State.hpp"
#include "KeyHandler.hpp"
#include "ButtonHandler.hpp"

class MainMenu : public State
{
public:
	MainMenu();
	~MainMenu();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler) override;
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler) override;
	void draw(sf::RenderTarget &target) override;

private:
	sf::Font m_font;
	KeyHandler m_keyHandler;
	ButtonHandler m_buttonHandler;
};

