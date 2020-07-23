#pragma once
#include <stack>
#include <vector>
#include "InputCommandMapper.h"
struct UserInput
{

	UserInput()
	{
		for (int i = 0; i < InputCommandMapper::commandTypeSize; ++i)
		{
			keyStates[i] = false;
			keyPressed[i] = false;
			keyReleased[i] = false;
		}
	}

	bool isPlayerOne = false;

	bool keyStates[InputCommandMapper::commandTypeSize];
	bool keyPressed[InputCommandMapper::commandTypeSize];
	bool keyReleased[InputCommandMapper::commandTypeSize];

};