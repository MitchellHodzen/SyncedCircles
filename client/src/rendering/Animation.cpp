#include "rendering/Animation.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include "KTime.h"

Animation::~Animation()
{
	ClearAnimation();
}

void Animation::ClearAnimation()
{
	animationSpriteIndicies.clear();
	animationLength = 0;
	name.clear();
}

bool Animation::GenerateAnimation(const std::string name, const std::vector<int> animationSpriteIndicies)
{
	bool success = true;
	if (!name.empty())
	{
		this->name = name;
		this->animationLength = animationSpriteIndicies.size();
		if (animationLength > 0)
		{
			for(int i = 0; i < animationLength; ++i)
			{
				this->animationSpriteIndicies.push_back(animationSpriteIndicies.at(i));
			}
		}
		else
		{
			std::cout<<"Empty animation sprite index vector supplied"<<std::endl;
			success = false;
		}
	}
	else
	{
		std::cout<<"No name supplied to animation"<<std::endl;
		success = false;
	}

	if (!success)
	{
		//If not successful, clear animation
		ClearAnimation();
	}

	return success;

}

int Animation::GetSpriteAtIndex(int spriteIndex)
{
	return animationSpriteIndicies.at(spriteIndex);
}

unsigned int Animation::GetAnimationLength()
{
	return this->animationLength;
}

std::string Animation::GetName()
{
	return this->name;
}
