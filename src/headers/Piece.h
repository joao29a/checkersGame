#ifndef PIECE_H
#define PIECE_H

#include "defines.h"

class Piece{
	protected:
		int life;
	public:
		Piece();
		int color;
		virtual bool checkMove();
		void promotePiece();
};

#endif
