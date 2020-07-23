#include "rendering/KRenderer.h"
#include "rendering/Texture.h"
#include "Rectangle.h"

KRenderer::~KRenderer()
{
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	sdlRenderer = nullptr;
	sdlWindow = nullptr;
	IMG_Quit();
	SDL_Quit();
}

void KRenderer::ClearScreen()
{
	SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(sdlRenderer);
}

void KRenderer::RenderTexture(Texture& texture, int posX, int posY, Rectangle& cutRect, bool flipped)
{
	//flip defaults to SDL_FLIP_NONE
	SDL_RendererFlip renderFlip = SDL_FLIP_NONE;
	if (flipped == true)
	{
		renderFlip = SDL_FLIP_HORIZONTAL;
	}
	
	SDL_Rect sdlCutRect{ cutRect.posX, cutRect.posY, cutRect.width, cutRect.height };

	//If we want the position to be the middle, do this calculation
	SDL_Rect sdlPosRect{ posX - sdlCutRect.w / 2, posY - sdlCutRect.h / 2, sdlCutRect.w, sdlCutRect.h };
	
	//If we want the position to be the top left do this calcuation
	//SDL_Rect sdlPosRect{ posX, posY, sdlCutRect.w, sdlCutRect.h };

	//Not a memory leak? Memory is just slowly allocated but has an upper bounds
	SDL_RenderCopyEx(sdlRenderer, texture.GetTexture(), &sdlCutRect, &sdlPosRect, 0.0, NULL, renderFlip);

}

void KRenderer::DrawRectangle(Rectangle& rectangle)
{
	SDL_Rect rect{ rectangle.posX, rectangle.posY, rectangle.width, rectangle.height };
    SDL_SetRenderDrawColor( sdlRenderer, 0x00, 0xFF, 0x00, 0xFF );        
    SDL_RenderDrawRect( sdlRenderer, &rect );
	//SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

}

void KRenderer::DrawScreen()
{
	SDL_RenderPresent(sdlRenderer);
}

bool KRenderer::Initialize(int screenWidth, int screenHeight)
{
	std::cout << "Initializing Renderer..." << std::endl;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized. SDL error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		sdlWindow = SDL_CreateWindow("Platform Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (sdlWindow == NULL)
		{
			std::cout << "SDL Window could not be created. SDL error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
			sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
			if (sdlRenderer == NULL)
			{
				std::cout << "SDL Renderer could not be created. SDL error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //old just white one
				//SDL_SetRenderDrawColor(sdlRenderer, 0xB9, 0xD9, 0xEE, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags)) & imgFlags)
				{
					std::cout << "SDL Img could not be initialized. SDL Img error: " << IMG_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}

int KRenderer::GetScreenWidth()
{
	return screenWidth;
}
int KRenderer::GetScreenHeight()
{
	return screenHeight;
}

SDL_Renderer* KRenderer::GetSdlRenderer()
{
	return sdlRenderer;
}