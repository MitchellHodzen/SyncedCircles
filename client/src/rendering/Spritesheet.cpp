#include "rendering/Spritesheet.h"
#include <iostream>
#include "Rectangle.h"
#include "rendering/Animation.h"

Spritesheet::~Spritesheet()
{
	ClearSpritesheet();
}

void Spritesheet::ClearSpritesheet()
{
	//Delete all the sprite rectangles
	delete[] spriteList;
	spriteList = nullptr;
	//Spritesheet does not own the texture, so don't destroy it just dereference it
	texture = nullptr;
	//Reset all values to 0
	int spriteWidth = 0;
	int spriteHeight = 0;
	int rows = 0;
	int columns = 0;
	int spriteCount = 0;
	name.clear();
}

bool Spritesheet::GenerateSpritesheet(Texture& texture, std::string name, int spriteWidth, int spriteHeight, int rows, int columns, int spriteCount)
{
	bool success = true;

	this->texture = &texture;

	if (!name.empty())
	{
		this->name = name;
		if (spriteWidth > 0 && spriteHeight > 0)
		{
			this->spriteWidth = spriteWidth;
			this->spriteHeight = spriteHeight;

			if (rows > 0 && columns > 0)
			{
				this->rows = rows;
				this->columns = columns;

				if (spriteCount > 0)
				{
					this->spriteCount = spriteCount;

					//Instantiate our list of sprite rectangles
					spriteList = new Rectangle[spriteCount];

					//Starting at the top left of the spritesheet, move left to right
					int currentRow = 0;
					int currentColumn = 0;
					for(int i = 0; i < spriteCount; ++i)
					{
						//If we've passed the last column in the spritesheet, go to the next row
						if (currentColumn >= columns)
						{
							currentRow++;
							currentColumn = 0;
						}

						//For each sprite in the spritesheet, find the sprite rectangle
						spriteList[i].posX = currentColumn * spriteWidth;
						spriteList[i].posY = currentRow * spriteHeight;
						spriteList[i].width = spriteWidth - 1;
						spriteList[i].height = spriteHeight - 1;

						currentColumn ++;
						
					}
				}
				else
				{
					std::cout<<"Spritesheet " << name << " must have at least one sprite"<<std::endl;
					success = false;
				}
			}
			else
			{
				std::cout<< "Must supply non-zero rows and columns to spritesheet " << name << std::endl;
				success = false;
			}
		}
		else
		{
			std::cout<< "Must supply non-zero sprite dimensions to spritesheet " << name << std::endl;
			success = false;
		}
	}
	else
	{
		std::cout<< "No name supplied to spritesheet" << std::endl;
		success = false;
	}

	if (!success)
	{
		//If creating the spritesheet was not successful, clear the spritesheet
		ClearSpritesheet();
	}
	
	return success;
}

bool Spritesheet::GenerateAnimation(const std::string animationName, const std::vector<int> animationSpriteIndicies)
{
	std::cout << "Loading animation " << animationName << " for spritesheet " << this->GetName() << std::endl;
	Animation* animation = new Animation();
	bool success = animation->GenerateAnimation(animationName, animationSpriteIndicies);
	if (success)
	{
		animationPointerMap->insert_or_assign(animationName, animation);
	}
	return success;
}

Texture* Spritesheet::GetTexture()
{
	return texture;
}

Rectangle* Spritesheet::GetSprite(unsigned int spriteIndex)
{
	if (spriteIndex < spriteCount){
		return &(spriteList[spriteIndex]);
	}
	return nullptr;
}

Animation* Spritesheet::GetAnimation(std::string animationName)
{
	if (animationPointerMap->count(animationName))
	{
		return animationPointerMap->at(animationName);
	}
	return nullptr;
}


int Spritesheet::GetSpriteCount()
{
	return spriteCount;
}

int Spritesheet::GetSpriteHeight()
{
	return spriteHeight;
}

int Spritesheet::GetSpriteWidth()
{
	return spriteWidth;
}

std::string Spritesheet::GetName()
{
	return name;
}

void Spritesheet::PrintSpritesheetData()
{
	for(int i = 0; i < spriteCount; ++i)
	{
		std::cout<<"Sprite " << i << ":"<<std::endl;
		std::cout<<"\tX: " << spriteList[i].posX<<std::endl;
		std::cout<<"\tY: " << spriteList[i].posY<<std::endl;
		std::cout<<"\tRight: " << spriteList[i].posX + spriteList[i].width - 1 << std::endl;
		std::cout<<"\tBottom: " << spriteList[i].posY + spriteList[i].height - 1 << std::endl;
		std::cout<<"\tWidth: " << spriteList[i].width<<std::endl;
		std::cout<<"\tHeight: " << spriteList[i].height<<std::endl;
	}
}