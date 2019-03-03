#pragma once
#include "State.hpp"

enum class Transition
{
	None,
	Push,
	Pop,
	Reset
};


class StateHandler
{
public:
	State* GetState()
	{ 
		if (m_stateStack.empty())
			return nullptr;
		return m_stateStack.back().get();
	}

	bool InTransition()
	{
		return m_transition != Transition::None;
	}

	void PerformTransition(sf::Window &window, StateHandler &stateHandler) 
	{
		if (m_transition == Transition::Pop)
			m_stateStack.pop_back();

		if (m_transition == Transition::Reset)
			m_stateStack.clear();

		if (m_queuedState)
		{
			m_queuedState->init(window, stateHandler);
			m_stateStack.push_back(std::move(m_queuedState));
		}

		m_transition = Transition::None;
	}

	template <class T, class ...Args>
	State *Push(Args &&...args)
	{
		m_transition = Transition::Push;
		m_queuedState = std::make_unique<T>(
			std::forward(args)...);
		return m_queuedState.get();
	}

	template <class T, class ...Args>
	State *Switch(Args &&...args)
	{
		m_transition = Transition::Pop;
		m_queuedState = std::make_unique<T>(
			std::forward(args)...);
		return m_queuedState.get();
	}

	template <class T, class ...Args>
	State *Reset(Args &&...args)
	{
		m_transition = Transition::Reset;
		m_queuedState = std::make_unique<T>(
			std::forward(args)...);
		return m_queuedState.get();
	}

	void Pop()
	{
		m_transition = Transition::Pop;
	}

	void Exit()
	{
		m_transition = Transition::Reset;
	}

private:

	std::vector<std::unique_ptr<State>> m_stateStack;

	std::unique_ptr<State> m_queuedState;
	Transition m_transition = Transition::None;
};

