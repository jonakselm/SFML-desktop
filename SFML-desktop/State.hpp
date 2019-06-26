#pragma once

class StateHandler;
class State
{
public:
	State() = default;
	virtual ~State() = default;

	virtual bool pollEvent(sf::Window &window);
	virtual void init(sf::Window &window, StateHandler &stateHandler) = 0;
	virtual void handleExtraEvents(sf::Window &window, StateHandler &stateHandler) = 0;
	virtual void updateModel(sf::Window &window, StateHandler &stateHandler) = 0;
	virtual void draw(sf::RenderTarget &target) const = 0;

	bool isRespondable() { return m_respondable; }

private:
	bool m_respondable = true;
};
