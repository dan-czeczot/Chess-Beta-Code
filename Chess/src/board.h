#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>

#include <SDL2/SDL.h>

#include "piece.h"

namespace chs
{
	class Board
	{
	public:
		int board[64];
		SDL_Rect* selectedPiece;
		
		Board(SDL_Renderer* renderer, const char* fen);
		~Board();

		void determineMoves(bool hasClickedPiece, Piece piece, SDL_Point mousePos);

		void renderPieces(SDL_Renderer* renderer);

	private:
		std::vector<Piece> pieces; //could be array
		std::list<int> possibleMoves; //for the selected piece
		SDL_Texture* piecesTexture;
	};
}

#endif //BOARD_H