#pragma once

struct Rectangle
{
	Rectangle()
	{
		Rectangle(0, 0, 0, 0);
	};
	Rectangle(int posX, int posY, int width, int height)
	{
		this->posX = posX;
		this->posY = posY;
		this->width = width;
		this->height = height;
	};
	int posX, posY, width, height;
};

