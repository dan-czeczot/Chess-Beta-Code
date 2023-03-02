#ifndef PIECE_H
#define PIECE_H

namespace chs
{
	enum class Piece
	{
		NONE = 0,
		KING = 1,
		QUEEN = 2,
		BISHOP = 3,
		KNIGHT = 4,
		ROOK = 5,
		PAWN = 6,

		WHITE = 8,
		BLACK = 16
	};

	//list of move vectors for each type of piece
}

#endif //PIECE_H