#pragma once
#include "Button.hpp"
#include <optional>

class ButtonHandler
{
public:
	ButtonHandler() = default;
	~ButtonHandler() = default;

	void setFont(const sf::Font &font) { m_pFont = &font; }
	const sf::Font &getFont() const { return *m_pFont; }

	void setTextSize(unsigned int size);
	unsigned int getTextSize() const;

	void setSpacing(int spacing);
	int getSpacing() const;

	void setNextPosition(int x, int y);
	std::pair<int, int> getNextPosition() const;

	void setDefaultSize(int width, int height);
	std::pair<int, int> getDefaultSize() const;

	Button &addButton(const std::string &text, const std::function<void()> &func);

	void handleInput(sf::Window &window);
	void draw(sf::RenderTarget &target) const;

	auto &buttons() { return m_buttons; }
	const auto &buttons() const { return m_buttons; }

	//auto &operator[](size_t index) { return m_buttons[index]; }
	//const auto &operator[](size_t index) const { return m_buttons[index]; }
private:
	bool toogleInputMode();
	void handleKeyEvents(sf::Window &window);
	void handleMouseEvents(sf::Window &window); // TODO: implement, pollevent

private:
	sf::Vector2i m_lastMousePos;
	std::optional<bool> m_mouseControl;
	int m_defaultWidth = 250, m_defaultHeight = 60;
	int m_xCurr = 0, m_yCurr = 0;
	int m_spacing = 10;
	int m_textSize = 30;
	std::list<Button> m_buttons;
	decltype(m_buttons)::iterator m_it;
	const sf::Font *m_pFont = nullptr;

	bool m_updatable = true;
	const sf::Time m_updatePeriod = sf::milliseconds(100);
	sf::Clock m_clock;
	sf::Time m_time;
};

