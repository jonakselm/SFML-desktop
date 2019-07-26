#pragma once

#include "State.hpp"
#include "ButtonHandler.hpp"
#include "KeyHandler.hpp"
#include "PlatformHandler.hpp"
#include "Player.hpp"
#include <array>
#include "CameraControl.hpp"

class Platformer : public State
{
private:
	enum class LastDir { None, Left, Right, Up };

public:
	Platformer();
	virtual ~Platformer();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler);
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler);
	void draw(sf::RenderTarget &target) const;

private:
	sf::Clock m_clock;
	sf::Font m_font;
	sf::Text m_currText, m_prevText;
	std::array<std::string, 3> m_stringArr;
	std::array<sf::Text, 3> m_currArr;
	std::array<sf::Text, 3> m_prevArr;
	LastDir m_lastDir = LastDir::None;
	CameraControl m_cameraControl;
	ButtonHandler m_buttonHandler;
	KeyHandler m_keyHandler;
	PlatformHandler m_platformHandler;
	Player m_player;
	bool m_jumpable = true;
	const float m_speed = 0.4f, m_gravity = 0.35f;
};

