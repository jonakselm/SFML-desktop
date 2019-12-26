#pragma once
#include <functional>

struct MouseButtonEvent
{
	sf::Vector2i pos;
};

using MouseButtonEventFunc = std::function<void(MouseButtonEvent)>;

class MouseButtonInfo
{
public:
	MouseButtonInfo(sf::Mouse::Button button, bool isModal, const MouseButtonEventFunc &func)
		: m_buttons{ button }, m_isModal(isModal), m_func(func) {}

	MouseButtonInfo(std::vector<sf::Mouse::Button> buttons, bool isModal, const MouseButtonEventFunc &func)
		: m_buttons(buttons), m_isModal(isModal), m_func(func) {}

	void invoke(MouseButtonEvent e);
	bool isPressed() const;
	std::vector<sf::Mouse::Button> buttons() const;
	bool invokeIfReady();

private:
	bool m_isModal = false;
	bool m_wasPressed = true;
	std::vector<sf::Mouse::Button> m_buttons;
	MouseButtonEventFunc m_func;
};

class MouseButtonHandler
{
	// Maps a button into an action within an UI
	// Should not be used in menus
public:
	MouseButtonHandler() = default;
	~MouseButtonHandler() = default;

	MouseButtonInfo &addButton(MouseButtonInfo buttonInfo);
	MouseButtonInfo &onButtonPressed(sf::Mouse::Button button, const MouseButtonEventFunc &func);
	MouseButtonInfo &whileButtonPressed(sf::Mouse::Button button, const MouseButtonEventFunc &func);
	MouseButtonInfo &onButtonComboPressed(std::initializer_list<sf::Mouse::Button> buttons, const MouseButtonEventFunc &func);
	MouseButtonInfo &whileButtonComboPressed(std::initializer_list<sf::Mouse::Button> buttons, const MouseButtonEventFunc &func);

	void handleButtonInput();

private:
	std::list<MouseButtonInfo> m_buttons;
};
