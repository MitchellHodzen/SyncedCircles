#include "systems/RenderSystem.h"
#include "kecs/KECS.h"
#include "Components/c_transform.h"
#include "rendering/Texture.h"
#include "rendering/Spritesheet.h"
#include "rendering/Animation.h"
#include "Rectangle.h"
#include "rendering/KRenderer.h"

void RenderSystem::DrawPlayers(KRenderer& kRenderer)
{
	kRenderer.ClearScreen();
	
	std::vector<Entity> entities = EntityManager::GetEntitiesWithComponent<Transform>();

	for (Entity entity : entities)
	{
		//Most optimal way to do position memory wise? Take another look
		Transform* trans = EntityManager::GetComponent<Transform>(entity);
		Vector2 position = trans->position;
		
		if (EntityManager::IsValidEntity(trans->parentEntity))
		{
			//If there is a parent entity, add the transform
			Transform* parentTrans = EntityManager::GetComponent<Transform>(trans->parentEntity);
			if (parentTrans != nullptr)
			{
				position = Vector2::ComponentWiseAddition(trans->position, parentTrans->position);
			}
		}


		Rectangle rectangle(position.GetX(), position.GetY(), 50, 50);
		kRenderer.DrawRectangle(rectangle);
	}
}

void RenderSystem::DrawToScreen(KRenderer& kRenderer)
{
	kRenderer.DrawScreen();
}

