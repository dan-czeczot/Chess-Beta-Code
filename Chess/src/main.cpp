#include <iostream>

#include <SDL2/SDL.h>

#include "game.h"

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	//int count = 0;

	chs::Game game("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

	/*
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << board.board[i * 8 + j] << "\t";
		}
		std::cout << std::endl << std::endl;
	}
	*/

	while (game.gameIsRunning())
	{
		frameStart = SDL_GetTicks();

		game.processInput();
		game.update();
		game.render();

		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}

		//count++;
		//std::cout << count << std::endl;
	}

	game.~Game();

	return 0;
}