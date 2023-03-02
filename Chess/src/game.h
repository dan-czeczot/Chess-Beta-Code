#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "board.h"

namespace chs
{ 
	class Game
	{
	public:
		Game(const char* title, int x, int y, int w, int h, bool isFullscreen);
		~Game();

		void processInput();
		void update();
		void render();

		inline bool gameIsRunning()
		{
			return isRunning;
		}

		//SDL_Window* window;
		//SDL_Renderer* renderer;

	private:
		bool isRunning;

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* boardTexture;

		chs::Board* board;

		SDL_Point mousePos;
		int tempPiece;
	};
}

#endif //GAME_H