#include "systems/InputSystem.h"
#include "kecs/KECS.h"
#include "Components/c_input.h"
#include "Components/c_physics.h"
#include "MessageManager.h"
#include "InputManager.h"
#include "KTime.h"
#include "InputCommandMapper.h"

InputSystem::InputSystem()
{
	InputCommandMapper::GetInstance().MapInputToCommand(InputManager::KeyboardKey::KEY_S, InputCommandMapper::Command::MoveDown);
	InputCommandMapper::GetInstance().MapInputToCommand(InputManager::KeyboardKey::KEY_W, InputCommandMapper::Command::MoveUp);
	InputCommandMapper::GetInstance().MapInputToCommand(InputManager::KeyboardKey::KEY_A, InputCommandMapper::Command::MoveLeft);
	InputCommandMapper::GetInstance().MapInputToCommand(InputManager::KeyboardKey::KEY_D, InputCommandMapper::Command::MoveRight);
}


InputSystem::~InputSystem()
{
}

void InputSystem::GetUserInput()
{
	std::vector<Entity> entities = EntityManager::GetEntitiesWithComponent<UserInput>();

	//For every entity which captures user input, record user input
	for (Entity entity : entities)
	{
		UserInput* uin = EntityManager::GetComponent<UserInput>(entity);

		//Decide what commands to use
		InputCommandMapper::Command moveLeftCommand = InputCommandMapper::Command::MoveLeft;
		InputCommandMapper::Command moveRightCommand = InputCommandMapper::Command::MoveRight;
		InputCommandMapper::Command moveDownCommand = InputCommandMapper::Command::MoveDown;
		InputCommandMapper::Command moveUpCommand = InputCommandMapper::Command::MoveUp;

		uin->keyStates[InputCommandMapper::Command::MoveLeft] = InputCommandMapper::GetInstance().GetCommandDown(moveLeftCommand);
		uin->keyStates[InputCommandMapper::Command::MoveRight] = InputCommandMapper::GetInstance().GetCommandDown(moveRightCommand);
		uin->keyStates[InputCommandMapper::Command::MoveUp] = InputCommandMapper::GetInstance().GetCommandDown(moveUpCommand);
		uin->keyStates[InputCommandMapper::Command::MoveDown] = InputCommandMapper::GetInstance().GetCommandDown(moveDownCommand);

		uin->keyPressed[InputCommandMapper::Command::MoveLeft] = InputCommandMapper::GetInstance().GetCommandPressed(moveLeftCommand);
		uin->keyPressed[InputCommandMapper::Command::MoveRight] = InputCommandMapper::GetInstance().GetCommandPressed(moveRightCommand);
		uin->keyPressed[InputCommandMapper::Command::MoveUp] = InputCommandMapper::GetInstance().GetCommandPressed(moveUpCommand);
		uin->keyPressed[InputCommandMapper::Command::MoveDown] = InputCommandMapper::GetInstance().GetCommandPressed(moveDownCommand);

		uin->keyReleased[InputCommandMapper::Command::MoveLeft] = InputCommandMapper::GetInstance().GetCommandReleased(moveLeftCommand);
		uin->keyReleased[InputCommandMapper::Command::MoveRight] = InputCommandMapper::GetInstance().GetCommandReleased(moveRightCommand);
		uin->keyReleased[InputCommandMapper::Command::MoveUp] = InputCommandMapper::GetInstance().GetCommandReleased(moveUpCommand);
		uin->keyReleased[InputCommandMapper::Command::MoveDown] = InputCommandMapper::GetInstance().GetCommandReleased(moveDownCommand);
	}
}