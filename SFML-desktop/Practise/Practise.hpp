#pragma once
#include "../State.hpp"
#include "../KeyHandler.hpp"
#include "../ButtonHandler.hpp"

class Practise : public State
{
public:
	Practise();
	virtual ~Practise();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget &target) const;

private:
	float X, Y, Z, R;
	sf::Font font;
	sf::Text text, pauseText;
	ButtonHandler buttonHandler;
	KeyHandler keyHandler;
	std::array<sf::CircleShape, sf::Joystick::Count> m_players;
	std::array<bool, sf::Joystick::Count> m_spawned;
	bool m_showNumbers = false;
	bool m_showable = true;
	bool m_pause = false;
	bool m_pausable = true;
};

