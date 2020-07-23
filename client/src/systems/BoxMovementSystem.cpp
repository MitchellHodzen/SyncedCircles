#include "systems/BoxMovementSystem.h"
#include "kecs/KECS.h"
#include "Components/c_input.h"
#include "Components/c_physics.h"
#include "Components/c_transform.h"
#include "KTime.h"
#include "InputCommandMapper.h"


void BoxMovementSystem::UpdateBoxMovement()
{
	std::vector<Entity> entities = EntityManager::GetEntitiesWithComponent<UserInput, Physics>();

	for (Entity entity : entities)
	{
		UserInput* uin = EntityManager::GetComponent<UserInput>(entity);
		Physics* phys = EntityManager::GetComponent<Physics>(entity);

		float moveSpeed = 700;
		float maxSpeed = phys->maxSpeed;
		//Horizontal Movement
		if (uin->keyStates[InputCommandMapper::Command::MoveLeft])
		{
			//If left is pressed, apply left movement
			float currentVelocityX = phys->velocity.GetX();
			float newVelocityX = currentVelocityX - moveSpeed * KTime::GetDeltaTime();
			if (phys->velocity.GetX() > 0){
				//If we're moving right, give left movement a boost with friction
				newVelocityX -= phys->friction * KTime::GetDeltaTime();
			}
			phys->velocity.SetX(newVelocityX);
		}
		else if (uin->keyStates[InputCommandMapper::Command::MoveRight])
		{
			//If right is pressed, apply right movement
			float currentVelocityX = phys->velocity.GetX();
			float newVelocityX = currentVelocityX + moveSpeed * KTime::GetDeltaTime();
			if (phys->velocity.GetX() < 0){
				//If we're moving left, give right movement a boost with friction
				newVelocityX += phys->friction * KTime::GetDeltaTime();
			}
			phys->velocity.SetX(newVelocityX);
		}
		else{
			//If no horizontal input is selected, we apply horizontal friction
			if (phys->velocity.GetX() > 0){
				//If we're moving right, apply friction to the left
				phys->velocity.SetX(phys->velocity.GetX() - phys->friction * KTime::GetDeltaTime());

				//If after applying friction the velocity direction changed, zero the velocity out
				if (phys->velocity.GetX() < 0){
					phys->velocity.SetX(0);
				}

			}
			else if (phys->velocity.GetX() < 0){
				//If we're moving left, apply friction to the right
				phys->velocity.SetX(phys->velocity.GetX() + phys->friction * KTime::GetDeltaTime());

				//If after applying friction the velocity direction changed, zero the velocity out
				if (phys->velocity.GetX() > 0){
					phys->velocity.SetX(0);
				}
			}
		}




		//Vertical Movement
		if (uin->keyStates[InputCommandMapper::Command::MoveUp])
		{
			//If up is pressed, apply up movement
			float currentVelocityY = phys->velocity.GetY();
			float newVelocityY = currentVelocityY - moveSpeed * KTime::GetDeltaTime();
			if (phys->velocity.GetY() > 0){
				//If we're moving down, give up movement a boost with friction
				newVelocityY -= phys->friction * KTime::GetDeltaTime();
			}
			phys->velocity.SetY(newVelocityY);
		}
		else if (uin->keyStates[InputCommandMapper::Command::MoveDown])
		{
			//If down is pressed, apply down movement
			float currentVelocityY = phys->velocity.GetY();
			float newVelocityY = currentVelocityY + moveSpeed * KTime::GetDeltaTime();
			if (phys->velocity.GetY() < 0){
				//If we're moving up, give down movement a boost with friction
				newVelocityY += phys->friction * KTime::GetDeltaTime();
			}
			phys->velocity.SetY(newVelocityY);
		}
		else{
			//If no vertical input is selected, we apply vertical friction
			if (phys->velocity.GetY() > 0){
				//If we're moving down, apply friction to the up
				phys->velocity.SetY(phys->velocity.GetY() - phys->friction * KTime::GetDeltaTime());

				//If after applying friction the velocity direction changed, zero the velocity out
				if (phys->velocity.GetY() < 0){
					phys->velocity.SetY(0);
				}

			}
			else if (phys->velocity.GetY() < 0){
				//If we're moving up, apply friction to the down
				phys->velocity.SetY(phys->velocity.GetY() + phys->friction * KTime::GetDeltaTime());

				//If after applying friction the velocity direction changed, zero the velocity out
				if (phys->velocity.GetY() > 0){
					phys->velocity.SetY(0);
				}
			}
		}

		//Clamping speed to max speed
		if (phys->velocity.GetMagnitude() > maxSpeed)
		{
			phys->velocity.SetMagnitude(maxSpeed);
		}
	}
}