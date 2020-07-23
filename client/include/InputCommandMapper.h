#pragma once
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "InputManager.h"

class InputCommandMapper
{
public:
	enum Command{MoveLeft, MoveRight, MoveUp, MoveDown};

	static InputCommandMapper& GetInstance()
	{
		//No need to check if the instance exists, C++ won't create another static instance
		//Also thread safe by default, C++ automatically locks on instance creation
		static InputCommandMapper instance;
		return instance;
	}

	~InputCommandMapper()
	{
		commandInputMap->clear();
		delete commandInputMap;
	}

	void MapInputToCommand(InputManager::KeyboardKey key, Command command)
	{
		commandInputMap->insert_or_assign(command, key);
	}

	InputManager::KeyboardKey GetInputFromCommand(Command command)
	{
		if (commandInputMap->count(command)) 
		{
			return commandInputMap->at(command);
		}
		return InputManager::KeyboardKey::UNMAPPED;
	}

	bool GetCommandDown(Command command)
	{
		InputManager::KeyboardKey key = GetInputFromCommand(command);
		if (key != InputManager::KeyboardKey::UNMAPPED)
		{
			return InputManager::GetInstance().GetKeyDown(key);
		}
		return false;
	}

	bool GetCommandPressed(Command command)
	{
		InputManager::KeyboardKey key = GetInputFromCommand(command);
		if (key != InputManager::KeyboardKey::UNMAPPED)
		{
			return InputManager::GetInstance().GetKeyPressed(key);
		}
		return false;
	}

	bool GetCommandReleased(Command command)
	{
		InputManager::KeyboardKey key = GetInputFromCommand(command);
		if (key != InputManager::KeyboardKey::UNMAPPED)
		{
			return InputManager::GetInstance().GetKeyReleased(key);
		}
		return false;
	}

	static const unsigned int commandTypeSize = 4;

private:
	InputCommandMapper() {}
	//static InputCommandMapper instance;

	std::unordered_map<Command, InputManager::KeyboardKey>* commandInputMap = new std::unordered_map<Command, InputManager::KeyboardKey>();
};