#include "systems/PhysicsSystem.h"
#include "kecs/KECS.h"
#include "Components/c_transform.h"
#include "Components/c_physics.h"
#include "Components/c_input.h"
#include "KTime.h"



PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::ApplyPhysics()
{
	std::vector<Entity> entities = EntityManager::GetEntitiesWithComponent<Transform, Physics>();
	for (Entity entity : entities)
	{
		Transform* trans = EntityManager::GetComponent<Transform>(entity);
		Physics* phys = EntityManager::GetComponent<Physics>(entity);

		//Apply delta time to velocity and assign the resulting vector to the movement vector
		Vector2 movementVector = phys->velocity * KTime::GetDeltaTime();

		//Delta time has already been applied
		trans->position += movementVector;
	}
}