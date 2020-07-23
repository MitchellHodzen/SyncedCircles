#include "rendering/Texture.h"
#include "rendering/KRenderer.h"

Texture::Texture()
{
	sdlTexture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	FreeTexture();

}

bool Texture::LoadTexture(std::string path, std::string name, KRenderer& kRenderer)
{
	bool success = true;
	FreeTexture();

	if (!name.empty())
	{
		this->name = name;

		if (!path.empty())
		{
			SDL_Surface* loadedSurface = IMG_Load(path.c_str());
			if (loadedSurface != NULL)
			{
				sdlTexture = SDL_CreateTextureFromSurface(kRenderer.GetSdlRenderer(), loadedSurface);
				if (sdlTexture != NULL)
				{
					width = loadedSurface->w;
					height = loadedSurface->h;
				}
				else
				{
					std::cout << "Unable to create texture. SDL error: " << SDL_GetError() << std::endl;
					success = false;
				}
				SDL_FreeSurface(loadedSurface);
			}
			else
			{
				std::cout << "Unable to load image at path: " << path << " SDL_Error: " << SDL_GetError() << std::endl;
				success = false;
			}
		}
		else
		{
			std::cout<<"No texture path supplied for " << name << std::endl;
			success = false;
		}
	}
	else
	{
		std::cout<<"No name supplied for texture"<<std::endl;
		success = false;
	}

	if (!success)
	{
		//If  not successful, free the texture
		FreeTexture();
	}
	
	return success;
}

void Texture::FreeTexture()
{
	if (sdlTexture != NULL)
	{
		SDL_DestroyTexture(sdlTexture);
		sdlTexture = NULL;
	}
	width = 0;
	height = 0;
	name.clear();
}

int Texture::GetWidth()
{
	return width;
}
int Texture::GetHeight()
{
	return height;
}
SDL_Texture* Texture::GetTexture()
{
	return sdlTexture;
}
std::string Texture::GetName()
{
	return name;
}