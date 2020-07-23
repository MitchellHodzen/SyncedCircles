#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Texture;
struct Rectangle;

class KRenderer
{
public:
	~KRenderer();
	bool Initialize(int screenWidth, int screenHeight);

	void ClearScreen();
	void RenderTexture(Texture& texture, int posX, int posY, Rectangle& cutRect, bool flipped);
	void DrawRectangle(Rectangle& rectangle);
	void DrawScreen();

	int GetScreenWidth();
	int GetScreenHeight();
	SDL_Renderer* GetSdlRenderer();

private:

	SDL_Renderer* sdlRenderer = nullptr;
	SDL_Window* sdlWindow = nullptr;
	int screenWidth = 0;
	int screenHeight = 0;
};

