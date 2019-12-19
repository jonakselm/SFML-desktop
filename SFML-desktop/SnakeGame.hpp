#pragma once
#include "State.hpp"
#include "ButtonHandler.hpp"
#include "KeyHandler.hpp"
#include "Snake.h"
#include "Location.h"
#include "FrameTimer.h"
#include "Apple.h"
#include "SnakeBot.hpp"

class SnakeGame : public State
{
private:
	enum class Dir { Up, Down, Left, Right };
public:
	SnakeGame(int nColors, const sf::Color &startColor, const Snake::ColorInit colorInit, int increment);
	virtual ~SnakeGame();

	void init(sf::Window &window, StateHandler &stateHandler);
	void updateModel(sf::Window &window, StateHandler &stateHandler) override;
	void handleExtraEvents(sf::Window &window, StateHandler &stateHandler) override;
	void draw(sf::RenderTarget &target) const override;

private:
	sf::Font font;
	sf::Text userScore, botScore;
	KeyHandler m_keyHandler;
	ButtonHandler buttonHandler;
	Board m_board;
	Snake m_snake;
	SnakeBot m_snakeBot;
	Apple m_apple;
	FrameTimer ft;

	bool m_pause = false;
	bool m_pausable = true;

	static constexpr float snakeMovePeriodMin = 0.06f;
	float snakeMovePeriod = 0.4f;
	float snakeMoveCounter = 0.0f;
	static constexpr float snakeSpeedupFactor = 0.005f;

	Dir currDir = Dir::Right;
	Dir prevDir;

	const int m_nColors;
	const sf::Color m_startColor;
	const Snake::ColorInit m_colorInit;
	const int m_increment;
	const SnakeBot::botState m_botState;
};

