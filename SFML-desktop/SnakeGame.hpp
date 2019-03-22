#pragma once
#include "State.hpp"
#include "Snake.h"
#include "Location.h"
#include "FrameTimer.h"
#include "KeyHandler.hpp"
#include "Apple.h"
#include "ButtonHandler.hpp"

class SnakeGame : public State
{
public:
	SnakeGame();
	virtual ~SnakeGame();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler) override;
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler) override;
	void draw(sf::RenderTarget &target) override;

private:
	sf::Font font;
	sf::Text score;
	KeyHandler keyHandler;
	ButtonHandler buttonHandler;
	Snake snake;
	Apple m_apple;
	Location delta_loc = { 1,0 };
	FrameTimer ft;
	int64_t lastTime;
	static constexpr float snakeMovePeriodMin = 0.06f;
	float snakeMovePeriod = 0.4f;
	float snakeMoveCounter = 0.0f;
	static constexpr float snakeSpeedupFactor = 0.005f;
	bool gameOver = false;
};

