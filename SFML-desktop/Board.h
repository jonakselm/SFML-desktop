#pragma once

#include "Location.h"

namespace Board
{
	void drawRect(const Location & loc, sf::Color c, sf::RenderTarget &target);
	void drawCircle(const Location & loc, sf::Color c, sf::RenderTarget & target);

	bool InsideBoard(const Location &loc);

	static constexpr int dim = 30;
	static constexpr int width = 33;
	static constexpr int height = 30;
};