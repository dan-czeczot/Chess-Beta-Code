#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace chs
{
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
}

#endif //TEXTURE_H