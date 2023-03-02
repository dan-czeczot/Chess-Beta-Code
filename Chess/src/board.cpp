#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <cmath>

#include <SDL2/SDL.h>

#include "board.h"
#include "piece.h"
#include "texture.h"

using namespace chs;

Board::Board(SDL_Renderer* renderer, const char* fen)
{
	piecesTexture = nullptr;

	//Establishes blank board
	for (int i = 0; i < 64; i++)
	{
		board[i] = (int)Piece::NONE;
	}

	//Reads fen position and sets pieces
	std::map<char, Piece> pieceDictionary =
	{
		{'k', Piece::KING},
		{'q', Piece::QUEEN},
		{'b', Piece::BISHOP},
		{'n', Piece::KNIGHT},
		{'r', Piece::ROOK},
		{'p', Piece::PAWN}
	};
	
	std::vector<std::string> fenParts;
	std::stringstream fenStream(fen);
	std::string strSection;
	while (std::getline(fenStream, strSection, ' '))
	{
		fenParts.push_back(strSection);
	}
	//Debug code
	for (std::string fenSeg : fenParts)
	{
		std::cout << fenSeg << std::endl;
	}

	int file = 0, rank = 7;
	for (char symbol : fenParts[0])
	{
		if (symbol == '/')
		{
			file = 0;
			rank--;
		}
		else if (std::isdigit(symbol))
		{
			file += (int)(symbol - '0');
		}
		else
		{
			Piece pieceColor;
			if (std::isupper(symbol))
			{
				pieceColor = Piece::WHITE;
			}
			else
			{
				pieceColor = Piece::BLACK;
			}
			Piece pieceType = pieceDictionary[std::tolower(symbol)];
			board[(rank * 8) + file] = (int)(pieceType) | (int)(pieceColor);
			file++;
		}
	}

	piecesTexture = chs::loadTexture(renderer, "assets/pieces.png");
	selectedPiece = nullptr;
}

Board::~Board()
{
	SDL_DestroyTexture(piecesTexture);
}

void Board::determineMoves(bool hasClickedPiece, Piece piece, SDL_Point mousePos)
{
	mousePos.x = std::floor(mousePos.x) / 100;
	mousePos.y = 8 - std::floor(mousePos.y) / 100;

	//check for each piece on the board, only check for spaces of val 0, and check for each move vector/possible move

	if (hasClickedPiece)
	{
		//check if king is in check

		switch (piece)
		{
		case Piece::KING:
			//Limit moves to own space and legal moves
			possibleMoves.push_front(board[(mousePos.y * 8) + mousePos.x]);


			break;
		}
	}
}

//function to move pieces

void Board::renderPieces(SDL_Renderer* renderer)
{
	for (int i = 0; i < 64; i++)
	{
		SDL_Rect srcR{}, destR{};
		srcR.w = 100;
		srcR.h = 100;
		destR.w = 100;
		destR.h = 100;

		if (board[i] != (int)Piece::NONE)
		{
			switch (board[i])
			{
			case (int)(Piece::KING) | (int)(Piece::BLACK):
				srcR.x = 0;
				srcR.y = 100;
				break;

			case (int)(Piece::QUEEN) | (int)(Piece::BLACK):
				srcR.x = 100;
				srcR.y = 100;
				break;

			case (int)(Piece::BISHOP) | (int)(Piece::BLACK):
				srcR.x = 200;
				srcR.y = 100;
				break;

			case (int)(Piece::KNIGHT) | (int)(Piece::BLACK):
				srcR.x = 300;
				srcR.y = 100;
				break;

			case (int)(Piece::ROOK) | (int)(Piece::BLACK):
				srcR.x = 400;
				srcR.y = 100;
				break;

			case (int)(Piece::PAWN) | (int)(Piece::BLACK):
				srcR.x = 500;
				srcR.y = 100;
				break;
			
			case (int)(Piece::KING) | (int)(Piece::WHITE):
				srcR.x = 0;
				srcR.y = 0;
				break;

			case (int)(Piece::QUEEN) | (int)(Piece::WHITE):
				srcR.x = 100;
				srcR.y = 0;
				break;

			case (int)(Piece::BISHOP) | (int)(Piece::WHITE):
				srcR.x = 200;
				srcR.y = 0;
				break;

			case (int)(Piece::KNIGHT) | (int)(Piece::WHITE):
				srcR.x = 300;
				srcR.y = 0;
				break;

			case (int)(Piece::ROOK) | (int)(Piece::WHITE):
				srcR.x = 400;
				srcR.y = 0;
				break;

			case (int)(Piece::PAWN) | (int)(Piece::WHITE):
				srcR.x = 500;
				srcR.y = 0;
				break;
			}

			destR.x = (i % 8) * 100;
			destR.y = 700 - (int)std::floor((double)i / 8) * 100;

			SDL_RenderCopy(renderer, piecesTexture, &srcR, &destR);
		}
		
	}
}