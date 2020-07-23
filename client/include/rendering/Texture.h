#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class KRenderer;

class Texture
{
public:
	Texture();
	~Texture();
	bool LoadTexture(std::string path, std::string name, KRenderer& kRenderer);
	void FreeTexture();
	int GetWidth();
	int GetHeight();
	SDL_Texture* GetTexture();
	std::string GetName();

private:
	SDL_Texture* sdlTexture;
	int width;
	int height;
	std::string name;
};

