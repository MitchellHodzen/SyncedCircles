#pragma once
#include <unordered_map>
#include <string>

//Forward declarations
class Texture;
class KRenderer;
class Spritesheet;

class ResourceManager
{
public:
	enum class TextureKey { Player, Bullet, Enemy, FighterSpritesheet};
	enum class SpritesheetKey { Fighter };

	static ResourceManager& GetInstance();
	bool Initialize(KRenderer& kRenderer);

	~ResourceManager();
	Texture* GetTexture(TextureKey key);
	Spritesheet* GetSpritesheet(SpritesheetKey key);

private:
	static ResourceManager instance;
	std::unordered_map<TextureKey, Texture*>* texturePointerMap = new std::unordered_map<TextureKey, Texture*>();;
	std::unordered_map<SpritesheetKey, Spritesheet*>* spritesheetPointerMap = new std::unordered_map<SpritesheetKey, Spritesheet*>();;

	ResourceManager() {}
	bool LoadTextures(KRenderer& kRenderer);
	bool LoadSpritesheets();
	void UnloadTextures();
	void UnloadSpritesheets();
	bool LoadTexture(std::string path, std::string name, TextureKey key, KRenderer& kRenderer);
	bool LoadSpritesheet(TextureKey textureKey, std::string name, int spriteWidth, int spriteHeight, int rows, int columns, int spriteCount, SpritesheetKey spritesheetKey);
};

