#pragma once

namespace sfExt
{
	class Joystick
	{
	public:
	};

	class Ps3
	{
	public:
		// Enum for cycling through the buttons easier
		enum Button
		{
			Select, L3, R3, Start, Up, Right, Down, Left, L2, R2,
			L1, R1, Triangle, Circle, Cross, Square, PS_Btn
		};

		static unsigned int getProductId()
		{
			return 616;
		}

		static bool isButtonPressed(unsigned int joystick, unsigned int button)
		{
			unsigned int id = sf::Joystick::getIdentification(joystick).productId;
			if (id == getProductId())
			{
				if (sf::Joystick::isButtonPressed(joystick, button))
					return true;
			}
			return false;
		}

	private:

	};

	class GameCube
	{
	public:
		// Enum for cycling through the buttons easier
		enum Button
		{
			X, A, B, Y, L, R, Z = 7, Start = 9, Up = 12, Right, Down, Left
		};

		static unsigned int getProductId()
		{
			return 6214;
		}

		static bool isButtonPressed(unsigned int joystick, unsigned int button)
		{
			unsigned int id = sf::Joystick::getIdentification(joystick).productId;
			if (id == getProductId())
			{
				if (sf::Joystick::isButtonPressed(joystick, button))
					return true;
			}
			return false;
		}
	};
}