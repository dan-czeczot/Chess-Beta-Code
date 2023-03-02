#include <iostream>
#include <cmath>

#include <SDL2/SDL.h>

#include "game.h"
#include "texture.h"

using namespace chs;

Game::Game(const char* title, int x, int y, int w, int h, bool isFullscreen)
{
	window = nullptr;
	renderer = nullptr;
	boardTexture = nullptr;

	try
	{
		int error;
			
		error = SDL_Init(SDL_INIT_EVERYTHING);
		if (error != 0)
		{
			error = 0;
			throw error;
		}

		window = SDL_CreateWindow(title, x, y, w, h, isFullscreen);
		if (window == nullptr)
		{
			error = 1;
			throw error;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer == nullptr)
		{
			error = 2;
			throw error;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}
	catch (int& error)
	{
		switch (error)
		{
		case 0:
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
			break;

		case 1:
			std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			break;

		case 2:
			std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			break;
		}
		
	}

	//prevents screen size bug
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");

	board = new chs::Board(renderer, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	boardTexture = chs::loadTexture(renderer, "assets/board.png");

	isRunning = true;

	int tempPiece = 0;
}

Game::~Game()
{
	isRunning = false;

	delete board;
	board = nullptr;

	SDL_DestroyTexture(boardTexture);
	boardTexture = nullptr;
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

void Game::processInput()
{
	SDL_Event input;
	SDL_PollEvent(&input);

	switch (input.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

		//PROTOTYPE CODE
	case SDL_MOUSEBUTTONDOWN:
		if (input.button.button == SDL_BUTTON_LEFT && tempPiece == 0)
		{
			//Pickup piece
			mousePos = { input.motion.x, input.motion.y };
			mousePos.x = std::floor(mousePos.x) / 100;
			mousePos.y = 8 - std::floor(mousePos.y) / 100;

			tempPiece = board->board[(mousePos.y * 8) + mousePos.x];
			board->board[(mousePos.y * 8) + mousePos.x] = 0;
			//Debug code
			std::cout << tempPiece << std::endl;

			//switch bool for piece pickup true
			

		}
		else if (input.button.button == SDL_BUTTON_LEFT && tempPiece != 0)
		{
			//Place piece
			mousePos = { input.motion.x, input.motion.y };
			mousePos.x = std::floor(mousePos.x) / 100;
			mousePos.y = 8 - std::floor(mousePos.y) / 100;

			board->board[(mousePos.y * 8) + mousePos.x] = tempPiece;
			tempPiece = 0;

			//switch bool for piece pickup false
		}
		break;

	default:
		break;
	}
}

void Game::update()
{
	//check board pos and legal moves for current turn

}

void Game::render()
{
	SDL_RenderClear(renderer);

	//Render Code
	SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
	board->renderPieces(renderer);

	SDL_RenderPresent(renderer);
}