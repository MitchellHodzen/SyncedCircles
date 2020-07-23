#pragma once
#include "Vector2.h"
#include "kecs/KECS.h"
struct Transform 
{
	Transform()
	{
		position.SetX(0);
		position.SetY(0);
		parentEntity = -1;
	};

	Vector2 position;
	Entity parentEntity;
};