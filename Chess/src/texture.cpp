#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.h"

SDL_Texture* chs::loadTexture(SDL_Renderer* renderer, const char* path)
{
	SDL_Texture* texture = nullptr;

	/*
	SDL_Surface* surface = IMG_Load(path);
	if (surface == nullptr)
	{
		std::cerr << "IMG_Load Error: " << IMG_GetError << std::endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == nullptr)
		{
			std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		}

		SDL_FreeSurface(surface);
	}
	*/

	texture = IMG_LoadTexture(renderer, path);
	if (texture == nullptr)
	{
		std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
	}

	return texture;


}