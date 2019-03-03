#pragma once
#include <functional>

class KeyInfo
{
public:
	KeyInfo(sf::Keyboard::Key key, const std::function<void()> &func) : m_key(key), m_func(func) {}

	void invoke() { m_func(); }
	bool isPressed() { return sf::Keyboard::isKeyPressed(m_key); }
	sf::Keyboard::Key key() { return m_key; }

private:
	sf::Keyboard::Key m_key;
	std::function<void()> m_func;
};


class KeyHandler
{
public:
	KeyInfo &addKey(sf::Keyboard::Key key, const std::function<void()> &func)
	{
		return m_keys.emplace_back(key, func);
	}

	void handleKeyInput()
	{
		for (auto &key : m_keys)
		{
			if (key.isPressed())
				key.invoke();
		}
	}

private:
	std::list<KeyInfo> m_keys;
};
