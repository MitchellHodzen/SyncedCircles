#pragma once
#include <string>
#include <unordered_map>
#include <vector>
class Texture;
class Rectangle;
class Animation;

class Spritesheet
{
public:
	~Spritesheet();

	bool GenerateSpritesheet(Texture& texture, std::string name, int spriteWidth, int spriteHeight, int rows, int columns, int spriteCount);

	bool GenerateAnimation(const std::string animationName, const std::vector<int> animationSpriteIndicies);

	Texture* GetTexture();
	Rectangle* GetSprite(unsigned int spriteIndex);
	Animation* GetAnimation(std::string animationName);

	int GetSpriteCount();
	int GetSpriteHeight();
	int GetSpriteWidth();
	std::string GetName();

	void PrintSpritesheetData();

private:

	void ClearSpritesheet();
	
	std::unordered_map<std::string, Animation*>* animationPointerMap = new std::unordered_map<std::string, Animation*>();;

	Rectangle* spriteList = nullptr;
	Texture* texture = nullptr;
	int spriteWidth = 0;
	int spriteHeight = 0;
	int rows = 0;
	int columns = 0;
	int spriteCount = 0;
	std::string name;
};

