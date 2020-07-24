#pragma once
#include "../State.hpp"
#include "BrickGrid.hpp"
#include "Ball.hpp"
#include "BallPad.hpp"
#include "../KeyHandler.hpp"

class BrickBreaker : public State
{
public:
	BrickBreaker();
	~BrickBreaker();

	void init(sf::Window &window, StateHandler &stateHandler) override;
	void updateModel(sf::Window &window, StateHandler &stateHandler) override;
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler) override;
	void draw(sf::RenderTarget &target) override;

private:
	KeyHandler keyHandler;
	sf::Font m_font;
	sf::Text m_elapsedTimeText, m_ballPosText;

	sf::Clock m_clock;
	sf::Time m_elapsedTime;

	BrickGrid m_brickGrid;
	Ball m_ball;
	BallPad m_pad;
};