#include "stdafx.h"
#include "CameraControl.hpp"


CameraControl::CameraControl(Player &player, PlatformHandler &platformHandler)
	:
	m_player(player),
	m_platformHandler(platformHandler)
{
}


CameraControl::~CameraControl()
{
}

void CameraControl::move(float x, float y)
{
	m_player.move(x, y);
	m_player.incrementStartY(y);
	m_platformHandler.moveAll(x, y);
}
