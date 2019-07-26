#pragma once

#include "PlatformHandler.hpp"
#include "Player.hpp"

class CameraControl
{
public:
	CameraControl(Player &player, PlatformHandler &platformHandler);
	~CameraControl();

	void move(float x, float y);

private:
	Player &m_player;
	PlatformHandler &m_platformHandler;
};

