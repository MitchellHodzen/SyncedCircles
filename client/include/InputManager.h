#pragma once
#include <SDL.h>
#include <iostream>
class InputManager
{
public:

	enum KeyboardKey{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_SHIFT, KEY_W, KEY_S,
						KEY_A, KEY_D, KEY_NUM_0, KEY_CTRL_R, UNMAPPED};

	static InputManager& GetInstance()
	{
		//No need to check if the instance exists, C++ won't create another static instance
		//Also thread safe by default, C++ automatically locks on instance creation
		static InputManager instance;
		return instance;
	}

	void UpdateInput()
	{
		//Clear the pressed and released arrays
		ClearInputArrays();

		//Use SDL poll events to get keyboard events. Allows for multiple events to happen on a key during one frame
		while (SDL_PollEvent(&inputEvent) != 0)
		{
			if (inputEvent.type == SDL_QUIT)
			{
				quit = true;
			}
			else if(inputEvent.type == SDL_KEYDOWN && inputEvent.key.repeat == false)
			{
				//Set pressed key array if the event is a key press and it isn't a repeat of a previous key press
				pressedKeys[inputEvent.key.keysym.scancode] = true;
			}
			else if(inputEvent.type == SDL_KEYUP && inputEvent.key.repeat == false)
			{
				//Set released key array if the event is a key release and it isn't a repeat of a previous key release
				releasedKeys[inputEvent.key.keysym.scancode] = true;
			}
		}
		//Current key state is automatically updated after all events have been polled
	}

	bool GetKeyDown(KeyboardKey key)
	{
		return currentKeyStates[ConvertKeyboardKeyToScancode(key)];
	}

	bool GetKeyPressed(KeyboardKey key)
	{
		return pressedKeys[ConvertKeyboardKeyToScancode(key)];
	}

	bool GetKeyReleased(KeyboardKey key)
	{
		return releasedKeys[ConvertKeyboardKeyToScancode(key)];
	}

	bool ShouldQuit()
	{
		return quit;
	}

private:
	InputManager() {
		//Initialize the pressed and released keys arrays to false
		ClearInputArrays();
	}
	static InputManager instance;
	SDL_Event inputEvent;

	int keyArrayLength;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(&keyArrayLength);
	bool* pressedKeys = new bool[keyArrayLength];
	bool* releasedKeys = new bool[keyArrayLength];
	bool quit = false;

	void ClearInputArrays()
	{
		for(int i = 0; i < keyArrayLength; ++i)
		{
			pressedKeys[i] = false;
			releasedKeys[i] = false;
		}
	}

	Uint8 ConvertKeyboardKeyToScancode(KeyboardKey key)
	{
		//Converts a KeyboardKey enum to a SDL scancode;
		switch(key)
		{
			case KeyboardKey::KEY_UP:
				return SDL_SCANCODE_UP;
			case KeyboardKey::KEY_DOWN:
				return SDL_SCANCODE_DOWN;
			case KeyboardKey::KEY_LEFT:
				return SDL_SCANCODE_LEFT;
			case KeyboardKey::KEY_RIGHT:
				return SDL_SCANCODE_RIGHT;
			case KeyboardKey::KEY_SPACE:
				return SDL_SCANCODE_SPACE;
			case KeyboardKey::KEY_SHIFT:
				return SDL_SCANCODE_LSHIFT;
			case KeyboardKey::KEY_W:
				return SDL_SCANCODE_W;
			case KeyboardKey::KEY_S:
				return SDL_SCANCODE_S;
			case KeyboardKey::KEY_A:
				return SDL_SCANCODE_A;
			case KeyboardKey::KEY_D:
				return SDL_SCANCODE_D;
			case KeyboardKey::KEY_NUM_0:
				return SDL_SCANCODE_KP_0;
			case KeyboardKey::KEY_CTRL_R:
				return SDL_SCANCODE_RCTRL;
		}
		return 0; //Find a better value for error? 
	}

};