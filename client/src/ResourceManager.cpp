#include "ResourceManager.h"
#include "rendering/Texture.h"
#include "rendering/Spritesheet.h"
#include "rendering/KRenderer.h"
#include <vector>
ResourceManager::~ResourceManager()
{
	UnloadSpritesheets();
	delete spritesheetPointerMap;
	UnloadTextures();
	delete texturePointerMap;
}

ResourceManager& ResourceManager::GetInstance()
{
	//No need to check if the instance exists, C++ won't create another static instance
	//Also thread safe by default, C++ automatically locks on instance creation
	static ResourceManager instance;
	return instance;
}

bool ResourceManager::Initialize(KRenderer& kRenderer) {
	return LoadTextures(kRenderer) && LoadSpritesheets();
}

bool ResourceManager::LoadTextures(KRenderer& kRenderer)
{
	std::cout<<"Loading textures"<<std::endl;
	return 
		LoadTexture("./resources/sprites/ship1.png", "Ship", TextureKey::Player, kRenderer) && 
		LoadTexture("./resources/sprites/bullet1.png", "Bullet", TextureKey::Bullet, kRenderer) && 
		LoadTexture("./resources/sprites/enemy1.png", "Enemy", TextureKey::Enemy, kRenderer) && 
		LoadTexture("./resources/sprites/SwordfightCharacterSpritesheet.png", "Fighter Spritesheet", TextureKey::FighterSpritesheet, kRenderer);

}

bool ResourceManager::LoadSpritesheets()
{
	std::cout<<"Loading spritesheets"<<std::endl;
	return 
		LoadSpritesheet(TextureKey::FighterSpritesheet, "Fighter", 310, 249, 5, 4, 18, SpritesheetKey::Fighter) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("animTest", {0,1,2,3,12,13,14,0,4,5,6,7,12,13,14,0,8,9,10,11,12,13,14}) &&
		//Fighter animations
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("midGuard", {0}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("midReady", {1}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("midAttack", {2,3,12}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("highGuard", {4}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("highReady", {5}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("highAttack", {6,7,12}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("lowGuard", {8}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("lowReady", {9}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("lowAttack", {10,11,12}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("attackRecovery", {13,14,12}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("feetWalk", {17, 16}) &&
		GetSpritesheet(SpritesheetKey::Fighter)->GenerateAnimation("feetIdle", {16});
}

bool ResourceManager::LoadTexture(std::string path, std::string name, TextureKey key, KRenderer& kRenderer)
{
	std::cout << "Loading " << name << " texture at " << path << std::endl;
	Texture* texture = new Texture();
	bool success = texture->LoadTexture(path, name, kRenderer);
	if (success)
	{
		texturePointerMap->insert_or_assign(key, texture);
	}
	return success;
}

bool ResourceManager::LoadSpritesheet(TextureKey textureKey, std::string name, int spriteWidth, int spriteHeight, int rows, int columns, int spriteCount, SpritesheetKey spritesheetKey)
{
	std::cout<< "Loading " << name <<" spritesheet "<<std::endl;
	Spritesheet* spritesheet = new Spritesheet();
	Texture* texture = GetTexture(textureKey);
	if (texture != nullptr)
	{
		std::cout<< "\tAssigning spritesheet " << name << " texture " << texture->GetName() <<std::endl;

		if (spritesheet->GenerateSpritesheet(*texture, name, spriteWidth, spriteHeight, rows, columns, spriteCount))
		{
			spritesheetPointerMap->insert_or_assign(spritesheetKey, spritesheet);
			return true;
		}
		else
		{
			std::cout<<"Could not generate spritesheet " << name << std::endl;
			return false;
		}
		
	}
	else
	{
		std::cout<<"No texture found for spritesheet " << name << std::endl;
		return false;
	}
	
}

Texture* ResourceManager::GetTexture(TextureKey key)
{
	if (texturePointerMap->count(key))
	{
		return texturePointerMap->at(key);
	}
	return nullptr;
}

Spritesheet* ResourceManager::GetSpritesheet(SpritesheetKey key)
{
	if (spritesheetPointerMap->count(key))
	{
		return spritesheetPointerMap->at(key);
	}
	return nullptr;
}

void ResourceManager::UnloadTextures()
{
	texturePointerMap->clear();
}

void ResourceManager::UnloadSpritesheets()
{
	spritesheetPointerMap->clear();
}
